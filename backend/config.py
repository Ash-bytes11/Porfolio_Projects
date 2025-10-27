import os

# Database connection (Docker uses 'db' as hostname)
DB_DSN = os.getenv("DB_DSN", "postgresql://nba:nba@db:5432/nba")

# Ollama host endpoint (Docker uses 'ollama')
OLLAMA_HOST = os.getenv("OLLAMA_HOST", "http://ollama:11434")

# Embedding and LLM models
EMBED_MODEL = os.getenv("EMBED_MODEL", "nomic-embed-text")
LLM_MODEL = os.getenv("LLM_MODEL", "llama3.2:3b")
