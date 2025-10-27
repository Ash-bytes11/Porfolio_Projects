from fastapi import FastAPI
from fastapi.middleware.cors import CORSMiddleware
from pydantic import BaseModel
import sqlalchemy as sa
from sqlalchemy import text
from backend.config import DB_DSN, EMBED_MODEL, LLM_MODEL
from backend.utils import ollama_embed, ollama_generate
from backend.rag import detect_table
import re
from datetime import datetime, timedelta

app = FastAPI()

app.add_middleware(
    CORSMiddleware,
    allow_origins=["http://localhost:4200"],
    allow_credentials=True,
    allow_methods=["*"],
    allow_headers=["*"],
)

eng = sa.create_engine(DB_DSN)


class Q(BaseModel):
    question: str


def extract_date_from_question(text: str):
    """
    Attempt to extract a date (month, day, year) from a natural-language question.
    Returns a datetime object if detected, otherwise None.
    """
    text_lower = text.lower()

    # Example: "October 27, 2023" or "Dec 31 2024"
    month_regex = (
        r"(january|february|march|april|may|june|july|august|"
        r"september|october|november|december|jan|feb|mar|apr|"
        r"jun|jul|aug|sep|oct|nov|dec)"
    )

    # Example: "October 27, 2023" or "December 31"
    match = re.search(fr"{month_regex}\s+(\d{{1,2}})(?:st|nd|rd|th)?(?:,?\s*(\d{{4}}))?", text_lower)
    if match:
        month_str, day_str, year_str = match.group(1), match.group(2), match.group(3)
        month_str = month_str[:3].title()
        try:
            year = int(year_str) if year_str else datetime.now().year
            date = datetime.strptime(f"{month_str} {day_str} {year}", "%b %d %Y")
            return date
        except ValueError:
            pass

    # Example: numeric pattern like "12/31/2024" or "12-31-2024"
    match = re.search(r"(\d{1,2})[/-](\d{1,2})[/-](\d{2,4})", text)
    if match:
        m, d, y = match.groups()
        try:
            y = int(y) + 2000 if len(y) == 2 else int(y)
            return datetime(int(y), int(m), int(d))
        except ValueError:
            pass

    # Example: only year mentioned ("in 2024")
    match = re.search(r"\b(20\d{2})\b", text)
    if match:
        try:
            return datetime(int(match.group(1)), 1, 1)
        except ValueError:
            pass

    return None


def build_context(rows, table: str):
    """Format retrieved rows into readable context for the language model."""
    if not rows:
        return ""
    if table == "player_box_scores":
        return "\n".join(
            [
                f"Game {r['game_id']}: Player {r.get('player_name', r.get('person_id'))} "
                f"({r.get('team_name', r.get('team_id'))}) — "
                f"Points: {r.get('points', 0)}, Rebounds: {r.get('rebounds', 0)}, Assists: {r.get('assists', 0)}"
                for r in rows
            ]
        )
    else:
        formatted = []
        for r in rows:
            home, away = r["home_team_name"], r["away_team_name"]
            hp, ap = int(r["home_points"]), int(r["away_points"])
            date = str(r["game_timestamp"]).split(" ")[0]
            if hp > ap:
                winner, loser, score = home, away, f"{hp}-{ap}"
            else:
                winner, loser, score = away, home, f"{ap}-{hp}"
            formatted.append(f"On {date}, {winner} won {score} against {loser}.")
        return "\n".join(formatted)


@app.post("/api/chat")
def answer(q: Q):
    """Process a user question, retrieve relevant data, and generate an answer."""
    print(f"Received question: {q.question}")
    table = detect_table(q.question)
    print(f"→ Detected table: {table}")
    qvec = ollama_embed(EMBED_MODEL, q.question)

    # Attempt to extract a date using regex-based detection
    dt = extract_date_from_question(q.question)
    date_clause = ""
    params = {"q": qvec, "k": 5}

    if dt:
        start = (dt - timedelta(days=3)).strftime("%Y-%m-%d")
        end = (dt + timedelta(days=3)).strftime("%Y-%m-%d")
        date_clause = "AND gd.game_timestamp BETWEEN :start AND :end"
        params.update({"start": start, "end": end})
        print(f"→ Detected date window: {start} to {end}")

    with eng.begin() as cx:
        if table == "player_box_scores":
            sql = text("""
                SELECT 
                    pbs.game_id,
                    (pl.first_name || ' ' || pl.last_name) AS player_name,
                    t.name AS team_name,
                    pbs.points,
                    (pbs.offensive_reb + pbs.defensive_reb) AS rebounds,
                    pbs.assists
                FROM player_box_scores pbs
                JOIN players pl ON pbs.person_id = pl.player_id
                JOIN teams t ON pbs.team_id = t.team_id
                ORDER BY pbs.embedding <-> (:q)::vector
                LIMIT :k
            """)
        else:
            sql = text(f"""
                SELECT gd.game_id, gd.game_timestamp,
                       ht.name AS home_team_name,
                       at.name AS away_team_name,
                       gd.home_points, gd.away_points
                FROM game_details gd
                JOIN teams ht ON gd.home_team_id = ht.team_id
                JOIN teams at ON gd.away_team_id = at.team_id
                WHERE 1=1 {date_clause}
                ORDER BY gd.embedding <-> (:q)::vector
                LIMIT :k
            """)
            print(f"→ Using date filter: {date_clause if date_clause else 'none'}")

        rows = cx.execute(sql, params).mappings().all()

    print(f"→ Retrieved {len(rows)} rows from {table}")
    ctx = build_context(rows, table)
    if not ctx.strip():
        print("No context found. Skipping LLM call.")
        return {"answer": "No relevant data found in database.", "evidence": []}

    prompt = f"Use this context to answer accurately:\n{ctx}\n\nQ: {q.question}\nA:"
    print("→ Prompt preview:\n", prompt[:300], "...\n")

    try:
        resp = ollama_generate(LLM_MODEL, prompt)
    except Exception as e:
        print(f"LLM generation failed: {e}")
        resp = "No response generated."

    return {
        "answer": resp,
        "evidence": [{"table": table, "id": int(r['game_id'])} for r in rows],
    }
