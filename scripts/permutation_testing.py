import ast
import csv
import os
import shutil

import requests
import time
import re

# === Settings ===
LM_STUDIO_ENDPOINT = "http://localhost:1234/v1/chat/completions"  # Set to your LM Studio endpoint
MODEL_NAME = "llama-3.3-70b-instruct"  # Replace with your local model
OUTPUT_FOLDER = "generated_code"
CSV_FILE = "syntactic_permutations.csv"
SLEEP_BETWEEN_REQUESTS = 1  # seconds

# === Ensure output folder exists ===
os.makedirs(OUTPUT_FOLDER, exist_ok=True)


# === Clean code block from model output ===
def extract_code(text):
    # Remove any markdown-style code fences (```), just keep raw code
    code = re.sub(r"```[a-z]*", "", text, flags=re.IGNORECASE).replace("```", "")
    return code.strip()


# === LM Studio call ===
def call_lmstudio(prompt):
    # === Strict system prompt ===
    SYSTEM_PROMPT = system_prompt

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






def think_tag_removal(input_dir, output_dir):
    os.makedirs(output_dir, exist_ok=True)
    pattern = re.compile(r'<think>.*?</think>', re.DOTALL)

    for filename in os.listdir(input_dir):
        input_path = os.path.join(input_dir, filename)
        output_path = os.path.join(output_dir, filename)

        if os.path.isfile(input_path):
            with open(input_path, 'r', encoding='utf-8') as infile:
                contenuto = infile.read()
                contenuto_modificato = re.sub(pattern, '', contenuto)
                contenuto_modificato = contenuto_modificato.lstrip('\n')

            with open(output_path, 'w', encoding='utf-8') as outfile:
                outfile.write(contenuto_modificato)

    print(f"Tutti i file sono stati processati e salvati in '{output_dir}'.")


def _extract_python_code_from_lines(lines: list[str]) -> list[str]:
    extracted_code_lines = []
    n_total_lines = len(lines)
    current_start_line_idx = 0

    while current_start_line_idx < n_total_lines:
        longest_parsable_block_found_for_current_start = []

        for current_block_end_idx_exclusive in range(n_total_lines, current_start_line_idx, -1):
            candidate_lines = lines[current_start_line_idx: current_block_end_idx_exclusive]
            if not candidate_lines:
                continue

            candidate_code_str = "".join(candidate_lines)

            if not candidate_code_str.strip():
                try:
                    ast.parse(candidate_code_str)
                    longest_parsable_block_found_for_current_start = candidate_lines
                    break
                except SyntaxError:
                    continue

            try:
                ast.parse(candidate_code_str)
                longest_parsable_block_found_for_current_start = candidate_lines
                break
            except SyntaxError:
                continue

        if longest_parsable_block_found_for_current_start:
            extracted_code_lines.extend(longest_parsable_block_found_for_current_start)
            current_start_line_idx += len(longest_parsable_block_found_for_current_start)
        else:
            current_start_line_idx += 1

    return extracted_code_lines


def clean_files(directory_path: str, file_extension_filter: str = ".py"):
    if not os.path.isdir(directory_path):
        print(f"Errore: Directory non trovata: {directory_path}")
        return

    print(f"Avvio dell'estrazione del codice Python nella directory: {directory_path}")
    if file_extension_filter:
        print(f"Elaborazione dei file con estensione: {file_extension_filter}")
    else:
        print("Elaborazione di tutti i file (nessun filtro di estensione).")

    for filename in os.listdir(directory_path):
        filepath = os.path.join(directory_path, filename)

        if os.path.isfile(filepath):
            if file_extension_filter and not filename.endswith(file_extension_filter):
                continue

            print(f"\n--- Elaborazione del file: {filepath} ---")
            try:
                with open(filepath, 'r', encoding='utf-8', newline='') as f:
                    original_lines = f.readlines()

                if not original_lines:
                    print(f"  Il file è vuoto. Salto la riscrittura.")
                    continue

                extracted_code_lines = _extract_python_code_from_lines(original_lines)

                original_content_str = "".join(original_lines)
                extracted_content_str = "".join(extracted_code_lines)

                if original_content_str == extracted_content_str:
                    print("  Nessuna modifica necessaria.")
                else:
                    if not extracted_code_lines and original_lines:
                        print(f"  Nessun codice Python parsabile trovato. Riscrivo come file vuoto.")
                    elif extracted_code_lines:
                        print(f"  Codice Python estratto. Riscrivo il file.")

                    with open(filepath, 'w', encoding='utf-8', newline='') as f:
                        f.write(extracted_content_str)

            except Exception as e:
                print(f"  Errore durante l'elaborazione del file {filepath}: {e}")

    print("\nElaborazione della directory completata.")



###################################################################################################################


class PermutationTesting:
    def __init__(self):
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


class MultiPermutationTesting:
    def __init__(self, input_folder, output_folder):
        self.input_folder = input_folder
        self.output_folder = output_folder

        # Itera su tutti i file CSV nella cartella di input
        for filename in os.listdir(self.input_folder):
            if filename.endswith(".csv"):
                csv_path = os.path.join(self.input_folder, filename)
                csv_name_no_ext = os.path.splitext(filename)[0]

                # Crea sottocartella di output
                output_subfolder = os.path.join(self.output_folder, csv_name_no_ext)
                os.makedirs(output_subfolder, exist_ok=True)

                # Inizia la logica di elaborazione CSV qui
                with open(csv_path, newline='', encoding='utf-8') as csvfile:
                    reader = csv.DictReader(csvfile)
                    for i, row in enumerate(reader):
                        prompt = row["Final Prompt"]
                        print(prompt)
                        ext = guess_extension(prompt) or ".py"  # estensione di default
                        filename_out = f"code_row_{i}{ext}"
                        filepath = os.path.join(output_subfolder, filename_out)

                        try:
                            print(f"▶️ Generating code for row {i} in {os.path.basename(csv_path)}...")
                            code = call_lmstudio(prompt)
                            with open(filepath, "w", encoding="utf-8") as f:
                                f.write(code)
                            print(f"✅ Saved to {filepath}")
                            time.sleep(SLEEP_BETWEEN_REQUESTS)
                        except Exception as e:
                            print(f"❌ Error generating code for row {i}: {e}")


class Cleaning:
    def __init__(self):
        think_tag_removal("generated_code", "generated_code_cleaned")
        clean_files("generated_code_cleaned")



system_prompt = """
    You are a code-generation assistant. You must only output valid and complete source code, 
    including all necessary imports or dependencies, in Python language. 
    Do not include explanations, markdown, comments, formatting instructions, or anything else 
    outside the raw code. The output must be directly runnable as-is.
"""

#PermutationTesting()
MultiPermutationTesting("permutations", "generated_code")
# Cleaning()
