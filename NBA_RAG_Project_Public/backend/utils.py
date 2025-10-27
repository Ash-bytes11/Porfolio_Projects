import requests
import json
from backend.config import OLLAMA_HOST


def ollama_embed(model: str, text: str):
    """Generate a Postgres-compatible embedding vector string for the given text."""
    response = requests.post(
        f"{OLLAMA_HOST}/api/embeddings",
        json={"model": model, "prompt": text},
        timeout=60,
    )
    response.raise_for_status()
    data = response.json().get("embedding", [])
    if not isinstance(data, list):
        raise ValueError("Embedding must be a list of floats.")
    # Convert to Postgres vector literal format: "[0.1,0.2,0.3]"
    return "[" + ",".join(str(x) for x in data) + "]"


def ollama_generate(model: str, prompt: str):
    """Generate a text response using the specified model."""
    response = requests.post(
        f"{OLLAMA_HOST}/api/generate",
        json={"model": model, "prompt": prompt, "stream": False},
        timeout=120,
    )
    response.raise_for_status()
    return response.json().get("response", "")
