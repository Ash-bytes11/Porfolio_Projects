import os
import json
import sqlalchemy as sa
from sqlalchemy import text
from backend.config import DB_DSN, EMBED_MODEL, LLM_MODEL
from backend.utils import ollama_embed, ollama_generate

BASE_DIR = os.path.dirname(__file__)
QUESTIONS_PATH = os.path.normpath(os.path.join(BASE_DIR, "..", "part1", "questions.json"))
ANSWERS_PATH = os.path.normpath(os.path.join(BASE_DIR, "..", "part1", "answers.json"))
TEMPLATE_PATH = os.path.normpath(os.path.join(BASE_DIR, "..", "part1", "answers_template.json"))


def retrieve(cx, qvec, k=5, table="game_details"):
    """Retrieve the top-k rows from the specified table based on vector similarity."""
    sql = (
        f"SELECT *, 1 - (embedding <=> (:q)::vector) AS score "
        f"FROM {table} "
        f"ORDER BY embedding <-> (:q)::vector LIMIT :k"
    )
    return cx.execute(text(sql), {"q": qvec, "k": k}).mappings().all()


def detect_table(question: str):
    """Determine whether a question should query team data or player data."""
    q_lower = question.lower()

    player_names = [
        "lebron", "luka", "wembanyama", "shai", "curry", "doncic",
        "embiid", "jokic", "tatum", "giannis", "anthony davis", "booker",
        "sga", "fox", "harden", "lillard", "edwards", "murray"
    ]

    team_names = [
        "warriors", "lakers", "celtics", "thunder", "timberwolves", "nuggets",
        "mavericks", "hawks", "rockets", "spurs", "kings", "suns", "clippers",
        "bucks", "bulls", "heat", "knicks", "nets", "sixers", "raptors",
        "pelicans", "grizzlies", "magic", "jazz", "pistons", "hornets",
        "pacers", "wizards", "cavaliers"
    ]

    player_terms = [
        "player", "leading scorer", "who scored", "who led", "led all scorers",
        "top scorer", "recorded a triple-double", "triple-double", "double-double",
        "career-high", "individual", "stat line", "rebounds", "assists", "blocks",
        "steals", "had", "finished with", "performance", "score in his debut",
        "points did", "scorer", "player stats", "player performance"
    ]

    team_terms = [
        "team", "who won", "which team", "final score", "victory", "defeat",
        "beat", "win", "won over", "lost to", "game between", "match between",
        "versus", "against", "team total", "scored overall",
        "team performance", "score of the game"
    ]

    # Priority: explicit player phrases
    if any(p in q_lower for p in ["leading scorer", "who scored", "who led", "led all scorers"]):
        return "player_box_scores"

    # Handle ambiguous phrasing involving "how many points did"
    if "how many points did" in q_lower:
        if any(p in q_lower for p in player_names) or "player" in q_lower:
            return "player_box_scores"
        else:
            return "game_details"

    # Player-related detection
    if any(term in q_lower for term in player_terms) or any(p in q_lower for p in player_names):
        return "player_box_scores"

    # Team-related detection
    if any(term in q_lower for term in team_terms) or any(t in q_lower for t in team_names):
        return "game_details"

    # Default fallback
    return "game_details"


def build_context(rows):
    """Construct a textual context summary for retrieved rows."""
    if not rows:
        return "No context available."

    sample = rows[0]
    if "home_points" in sample and "away_points" in sample:
        return "\n".join([
            f"On {r['game_timestamp'].split('T')[0]}, "
            f"{r.get('home_team_city', '')} {r.get('home_team_name', r['home_team_id'])} "
            f"played against {r.get('away_team_city', '')} {r.get('away_team_name', r['away_team_id'])}. "
            f"{r.get('home_team_city', '')} {r.get('home_team_name', r['home_team_id'])} scored {r['home_points']} points "
            f"and {r.get('away_team_city', '')} {r.get('away_team_name', r['away_team_id'])} scored {r['away_points']} points."
            for r in rows
        ])
    else:
        return "\n".join([
            f"Player {r.get('player_name', r.get('person_id'))} from "
            f"{r.get('team_city', '')} {r.get('team_name', r.get('team_id'))} in game {r['game_id']} "
            f"scored {r.get('points', 0)} points, with {r.get('rebounds', 0)} rebounds "
            f"and {r.get('assists', 0)} assists."
            for r in rows
        ])


def answer(question_id, question, rows, table):
    """Generate a structured answer in JSON format for a given question and evidence context."""
    with open(TEMPLATE_PATH, encoding="utf-8") as f:
        template = json.load(f)

    ctx = build_context(rows)
    prompt = (
        f"You are a structured data generator.\n"
        f"Given NBA game data context, return ONLY valid JSON following this exact template:\n\n"
        f"{json.dumps(template, indent=2)}\n\n"
        f"Context:\n{ctx}\n\n"
        f"Question (id={question_id}): {question}\n\n"
        f"Respond only with a single JSON object. Do not include explanations or natural language."
    )

    try:
        raw = ollama_generate(LLM_MODEL, prompt).strip()
        parsed = json.loads(raw)
    except Exception as e:
        print(f"[WARN] Q{question_id}: generation or JSON parsing failed → {e}")
        parsed = template.copy()

    if isinstance(parsed, list) and parsed:
        parsed = parsed[0]

    parsed["id"] = question_id
    parsed.setdefault("result", {}).setdefault("evidence", [])
    parsed["result"]["evidence"] = [
        {"table": table, "id": int(r.get("game_id", 0))} for r in rows
    ]

    return parsed


if __name__ == "__main__":
    eng = sa.create_engine(DB_DSN)
    with open(QUESTIONS_PATH, encoding="utf-8") as f:
        qs = json.load(f)

    results = []
    with eng.begin() as cx:
        for q in qs:
            qid = q.get("id")
            question = q.get("question")
            print(f"\nProcessing Q{qid}: {question}")

            try:
                table = detect_table(question)
                qvec = ollama_embed(EMBED_MODEL, question)
                rows = retrieve(cx, qvec, 5, table)
                ans = answer(qid, question, rows, table)

                # Normalize output format for consistency
                result = ans.get("result", {})
                ev = result.get("evidence", [])
                ev_unique = [dict(t) for t in {tuple(d.items()) for d in ev}]

                qtype = "player" if table == "player_box_scores" else "team"

                clean_entry = {
                    "id": qid,
                    "type": qtype,
                    "question": question,
                    "result": {"evidence": ev_unique},
                }

                if qtype == "team":
                    clean_entry["result"].update({
                        "winner": result.get("winner", ""),
                        "score": result.get("score", ""),
                        "points": result.get("points", 0)
                    })
                else:
                    clean_entry["result"].update({
                        "player_name": result.get("player_name", ""),
                        "points": result.get("points", 0),
                        "rebounds": result.get("rebounds", 0),
                        "assists": result.get("assists", 0)
                    })

                results.append(clean_entry)
                print(f"✅ Q{qid} complete using table '{table}' ({len(rows)} rows)")

            except Exception as e:
                print(f"❌ Q{qid} failed: {e}")
                results.append({
                    "id": qid,
                    "type": "unknown",
                    "question": question,
                    "error": str(e),
                    "result": {"evidence": []},
                })

    with open(ANSWERS_PATH, "w", encoding="utf-8") as f:
        json.dump(results, f, ensure_ascii=False, indent=2)

    print(f"\n✅ Completed! Saved {len(results)} normalized answers to {ANSWERS_PATH}")
