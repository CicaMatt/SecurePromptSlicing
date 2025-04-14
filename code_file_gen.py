import csv
import os
import requests
import time
import re

# === Settings ===
LM_STUDIO_ENDPOINT = "http://localhost:1234/v1/chat/completions"  # Set to your LM Studio endpoint
MODEL_NAME = "qwen2.5-coder-14b-instruct"  # Replace with your local model
OUTPUT_FOLDER = "generated_code"
CSV_FILE = "syntactic_permutations.csv"
SLEEP_BETWEEN_REQUESTS = 1  # seconds

# === Strict system prompt ===
SYSTEM_PROMPT = (
    "You are a code-generation assistant. You must only output valid and complete source code, "
    "including all necessary imports or dependencies, for the language required by the prompt. "
    "Do not include explanations, markdown, comments, formatting instructions, or anything else "
    "outside the raw code. The output must be directly runnable as-is."
)

# === Ensure output folder exists ===
os.makedirs(OUTPUT_FOLDER, exist_ok=True)

# === Clean code block from model output ===
def extract_code(text):
    # Remove any markdown-style code fences (```), just keep raw code
    code = re.sub(r"```[a-z]*", "", text, flags=re.IGNORECASE).replace("```", "")
    return code.strip()

# === LM Studio call ===
def call_lmstudio(prompt):
    headers = {"Content-Type": "application/json"}
    payload = {
        "model": MODEL_NAME,
        "messages": [
            {"role": "system", "content": SYSTEM_PROMPT},
            {"role": "user", "content": prompt}
        ],
        "temperature": 0.7,
        "stream": False
    }

    response = requests.post(LM_STUDIO_ENDPOINT, headers=headers, json=payload)
    response.raise_for_status()
    result = response.json()

    if "choices" in result and len(result["choices"]) > 0:
        return extract_code(result["choices"][0]["message"]["content"])
    else:
        return "// No output returned by model"

def guess_extension(prompt):
    if "python" in prompt.lower():
        return ".py"
    elif "javascript" in prompt.lower() or "node" in prompt.lower():
        return ".js"
    elif "java" in prompt.lower():
        return ".java"
    elif "c++" in prompt.lower():
        return ".cpp"
    elif "c code" in prompt.lower() or "c program" in prompt.lower():
        return ".c"
    elif "go" in prompt.lower():
        return ".go"
    elif "rust" in prompt.lower():
        return ".rs"
    elif "bash" in prompt.lower():
        return ".sh"
    else:
        return ".txt"  # fallback


# === Main processing ===
with open(CSV_FILE, newline='', encoding='utf-8') as csvfile:
    reader = csv.DictReader(csvfile)
    for i, row in enumerate(reader):
        prompt = row["Resulting Prompt"]
        ext = guess_extension(prompt)
        filename = f"code_row_{i}{ext}"
        filepath = os.path.join(OUTPUT_FOLDER, filename)

        try:
            print(f"▶️ Generating code for row {i}...")
            code = call_lmstudio(prompt)
            with open(filepath, "w", encoding="utf-8") as f:
                f.write(code)
            print(f"✅ Saved to {filepath}")
            time.sleep(SLEEP_BETWEEN_REQUESTS)
        except Exception as e:
            print(f"❌ Error generating code for row {i}: {e}")
