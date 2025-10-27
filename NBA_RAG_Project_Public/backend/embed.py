import pandas as pd
import sqlalchemy as sa
from sqlalchemy import text
from backend.config import DB_DSN, EMBED_MODEL
from backend.utils import ollama_embed


def row_text(r):
    """Convert one game record into descriptive text for embedding."""
    ts = pd.to_datetime(r.game_timestamp, utc=True)
    date = ts.strftime('%Y-%m-%d')

    # Construct full team identifiers for improved semantic representation
    home_full = f"{r.home_team_city} {r.home_team_name}"
    away_full = f"{r.away_team_city} {r.away_team_name}"

    winner = home_full if int(r.home_points) > int(r.away_points) else away_full
    loser = away_full if winner == home_full else home_full

    return (
        f"On {date}, {home_full} played against {away_full}. "
        f"{home_full} scored {int(r.home_points)} points and {away_full} scored {int(r.away_points)} points. "
        f"{winner} defeated {loser} with a final score of "
        f"{max(int(r.home_points), int(r.away_points))}-"
        f"{min(int(r.home_points), int(r.away_points))}. "
        f"This was part of the {int(r.season)} NBA season."
    )


def player_row_text(r):
    """Convert one player performance record into descriptive text for embedding."""
    full_team = f"{r.team_city} {r.team_name}"
    return (
        f"Player {r.player_name} from {full_team} in game {int(r.game_id)} "
        f"scored {int(r.points)} points, with {int(r.rebounds)} rebounds and "
        f"{int(r.assists)} assists."
    )


def main():
    """Generate embeddings for game_details and player_box_scores tables."""
    print("Starting embedding process.")
    eng = sa.create_engine(DB_DSN)

    with eng.begin() as cx:
        cx.execute(text('ALTER DATABASE nba REFRESH COLLATION VERSION'))

        # --- GAME DETAILS EMBEDDINGS ---
        cx.execute(text("""
            ALTER TABLE IF EXISTS game_details
            ADD COLUMN IF NOT EXISTS embedding vector(768);
        """))
        cx.execute(text("""
            CREATE INDEX IF NOT EXISTS idx_game_details_embedding
            ON game_details USING hnsw (embedding vector_cosine_ops);
        """))

        # Include both team city and name for better contextual embeddings
        df = pd.read_sql(
            """
            SELECT gd.game_id, gd.season, gd.game_timestamp,
                   ht.city AS home_team_city, ht.name AS home_team_name,
                   at.city AS away_team_city, at.name AS away_team_name,
                   gd.home_points, gd.away_points
            FROM game_details gd
            JOIN teams ht ON gd.home_team_id = ht.team_id
            JOIN teams at ON gd.away_team_id = at.team_id
            ORDER BY gd.game_timestamp DESC, gd.game_id DESC
            """,
            cx,
        )

        for _, r in df.iterrows():
            vec = ollama_embed(EMBED_MODEL, row_text(r))
            cx.execute(
                text("UPDATE game_details SET embedding = :v WHERE game_id = :gid"),
                {"v": vec, "gid": int(r.game_id)},
            )

        print(f"Completed embeddings for game_details: {len(df)} rows updated.")

        # --- PLAYER BOX SCORES EMBEDDINGS ---
        cx.execute(text("""
            ALTER TABLE IF EXISTS player_box_scores
            ADD COLUMN IF NOT EXISTS embedding vector(768);
        """))
        cx.execute(text("""
            CREATE INDEX IF NOT EXISTS idx_player_box_scores_embedding
            ON player_box_scores USING hnsw (embedding vector_cosine_ops);
        """))

        # Include city and team name for player-level embeddings
        df_player = pd.read_sql(
            """
            SELECT pbs.game_id,
                   pbs.person_id AS player_id,
                   (pl.first_name || ' ' || pl.last_name) AS player_name,
                   t.city AS team_city,
                   t.name AS team_name,
                   pbs.points,
                   (pbs.offensive_reb + pbs.defensive_reb) AS rebounds,
                   pbs.assists
            FROM player_box_scores pbs
            JOIN players pl ON pbs.person_id = pl.player_id
            JOIN teams t ON pbs.team_id = t.team_id
            ORDER BY pbs.game_id DESC
            """,
            cx,
        )

        for _, r in df_player.iterrows():
            vec = ollama_embed(EMBED_MODEL, player_row_text(r))
            cx.execute(
                text("""
                    UPDATE player_box_scores
                    SET embedding = :v
                    WHERE game_id = :gid AND person_id = :pid
                """),
                {"v": vec, "gid": int(r.game_id), "pid": int(r.player_id)},
            )

        print(f"Completed embeddings for player_box_scores: {len(df_player)} rows updated.")

    print("All embeddings have been successfully generated.")


if __name__ == "__main__":
    main()
