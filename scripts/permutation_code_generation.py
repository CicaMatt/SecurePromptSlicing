import ast
import csv
import os
import shutil
import subprocess
from collections import defaultdict
from pathlib import Path

import pandas as pd
import requests
import time
import re


# === Settings ===
LM_STUDIO_ENDPOINT = "http://localhost:1234/v1/chat/completions"  # Set to your LM Studio endpoint
MODEL_NAME = "codellama-34b-instruct"  # Replace with your local model
BASELINE_FILE = "LLMSecEvalDataset.csv"
SLEEP_BETWEEN_REQUESTS = 1 #seconds

DEFAULT_OUTPUT_FOLDER = "generated_code"
DEFAULT_CSV_FILE = "syntactic_permutations.csv"



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
    elif "c" in prompt.lower() or "c" in prompt.lower():
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

    for root, _, files in os.walk(directory_path):
        for filename in files:
            if file_extension_filter and not filename.endswith(file_extension_filter):
                continue

            filepath = os.path.join(root, filename)
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


def replace_placeholder_in_csvs(folder_path: str, language: str):
    """
    Legge tutti i file CSV nella cartella specificata, sostituisce ogni occorrenza di <language>
    nella colonna 'Resulting Prompt' con la stringa fornita, crea una nuova colonna 'Final Prompt'
    con il risultato, e salva i file modificati sovrascrivendo gli originali.

    :param folder_path: Percorso della cartella contenente i file CSV.
    :param language: Stringa con cui sostituire il placeholder <language>.
    """
    for filename in os.listdir(folder_path):
        if filename.endswith(".csv"):
            file_path = os.path.join(folder_path, filename)
            try:
                df = pd.read_csv(file_path)

                if 'Resulting Prompt' in df.columns:
                    df['Final Prompt'] = df['Resulting Prompt'].astype(str).str.replace('<language>', language)
                    df.to_csv(file_path, index=False)
                else:
                    print(f"Colonna 'Resulting Prompt' non trovata in {filename}.")
            except Exception as e:
                print(f"Errore nella lettura del file {filename}: {e}")



def validate_snippets_and_csv(snippet_folder, csv_folder=None):
    """
    Validates the consistency between a snippet folder and a corresponding CSV folder:
    - If `snippet_folder` contains files directly, checks that there are exactly 150 visible files (ignores hidden files).
    - If it contains subfolders, for each subfolder:
        - Counts the number of visible snippet files inside it.
        - Looks for a CSV file in `csv_folder` with the same name as the subfolder.
        - Verifies that the number of data rows in the CSV (excluding the header) matches the number of snippet files.
        - At the end, prints the number of subfolders analyzed (ignoring hidden ones).
    """
    entries = [e for e in os.listdir(snippet_folder) if not e.startswith('.')]
    entry_paths = [os.path.join(snippet_folder, e) for e in entries]

    if all(os.path.isfile(p) for p in entry_paths):
        # Case 1: folder contains snippets directly
        snippet_files = [p for p in entry_paths if os.path.isfile(p) and not os.path.basename(p).startswith('.')]
        if len(snippet_files) == 150:
            print("OK: Exactly 150 visible snippet files found.")
        else:
            print(f"ERROR: Expected 150 visible snippet files, found {len(snippet_files)}.")
    else:
        # Case 2: folder contains subfolders with snippets
        folder_count = 0
        for entry in entries:
            subfolder_path = os.path.join(snippet_folder, entry)
            if os.path.isdir(subfolder_path) and not entry.startswith('.'):
                folder_count += 1
                snippet_files = [
                    f for f in os.listdir(subfolder_path)
                    if os.path.isfile(os.path.join(subfolder_path, f)) and not f.startswith('.')
                ]
                snippet_count = len(snippet_files)

                csv_path = os.path.join(csv_folder, f"{entry}.csv")
                if not os.path.isfile(csv_path):
                    print(f"ERROR: Missing CSV file for '{entry}'. Expected: {csv_path}")
                    continue

                with open(csv_path, newline='', encoding='utf-8') as csvfile:
                    reader = csv.reader(csvfile)
                    next(reader, None)  # Skip header row
                    csv_row_count = sum(1 for _ in reader)

                if snippet_count != csv_row_count:
                    print(f"MISMATCH: '{entry}': {snippet_count} snippets vs {csv_row_count} CSV rows (excluding header).")
                else:
                    print(f"OK: '{entry}' has {snippet_count} snippets and {csv_row_count} data rows in CSV.")

        print(f"\nTotal subfolders analyzed: {folder_count}")


###################################################################################################################


#class SetPermutationsLanguage:
#    def __init__(self):
#        replace_placeholder_in_csvs("permutations", language)


class BaselineCodeGeneration:
    def __init__(self):
        os.makedirs(baseline_folder, exist_ok=True)
        # === Main processing ===
        with open(BASELINE_FILE, newline='', encoding='utf-8') as csvfile:
            reader = csv.DictReader(csvfile)
            for i, row in enumerate(reader):
                prompt = row["Manually-fixed NL Prompt"]

                # Sostituzione del placeholder <language> con "Python"
                prompt = prompt.replace("<language>", language)

                ext = guess_extension(prompt) or extension  # Estensione di default se guess_extension fallisce
                filename = f"code_row_{i + 1}{ext}"
                filepath = os.path.join(baseline_folder, filename)

                try:
                    print(f"▶️ Generating code for row {i + 1}...")
                    code = call_lmstudio(prompt)
                    with open(filepath, "w", encoding="utf-8") as f:
                        f.write(code)
                    print(f"✅ Saved to {filepath}")
                    time.sleep(SLEEP_BETWEEN_REQUESTS)
                except Exception as e:
                    print(f"❌ Error generating code for row {i + 1}: {e}")


class SinglePermutationCodeGeneration:
    def __init__(self):
        os.makedirs(DEFAULT_OUTPUT_FOLDER, exist_ok=True)
        # === Main processing ===
        with open(DEFAULT_CSV_FILE, newline='', encoding='utf-8') as csvfile:
            reader = csv.DictReader(csvfile)
            for i, row in enumerate(reader):
                prompt_template = row["Resulting Prompt"]
                prompt = prompt_template.replace("<language>", language)
                print(prompt)
                ext = guess_extension(prompt)
                filename = f"code_row_{i}{ext}"
                filepath = os.path.join(DEFAULT_OUTPUT_FOLDER, filename)

                try:
                    print(f"▶️ Generating code for row {i}...")
                    code = call_lmstudio(prompt)
                    with open(filepath, "w", encoding="utf-8") as f:
                        f.write(code)
                    print(f"✅ Saved to {filepath}")
                    time.sleep(SLEEP_BETWEEN_REQUESTS)
                except Exception as e:
                    print(f"❌ Error generating code for row {i}: {e}")


class PermutationsCodeGeneration:
    def __init__(self):
        os.makedirs(output_folder, exist_ok=True)
        # Itera su tutti i file CSV nella cartella di input
        for filename in os.listdir(permutations_folder):
            if filename.endswith(".csv"):
                csv_path = os.path.join(permutations_folder, filename)
                csv_name_no_ext = os.path.splitext(filename)[0]

                # Crea sottocartella di output
                output_subfolder = os.path.join(output_folder, csv_name_no_ext)
                os.makedirs(output_subfolder, exist_ok=True)

                # Inizia la logica di elaborazione CSV qui
                with open(csv_path, newline='', encoding='utf-8') as csvfile:
                    reader = csv.DictReader(csvfile)
                    for i, row in enumerate(reader):
                        # Prende il prompt dalla colonna Resulting prompt e sostituisce <language>
                        prompt_template = row["Resulting Prompt"]
                        prompt = prompt_template.replace("<language>", language)
                        print(prompt)

                        ext = guess_extension(prompt) or extension  # estensione di default
                        filename_out = f"code_row_{i+1}{ext}"
                        filepath = os.path.join(output_subfolder, filename_out)

                        try:
                            print(f"▶️ Generating code for row {i+1} in {os.path.basename(csv_path)}...")
                            code = call_lmstudio(prompt)
                            with open(filepath, "w", encoding="utf-8") as f:
                                f.write(code)
                            print(f"✅ Saved to {filepath}")
                            time.sleep(SLEEP_BETWEEN_REQUESTS)
                        except Exception as e:
                            print(f"❌ Error generating code for row {i+1}: {e}")


class IntegrityCheck:
    def __init__(self, snippets_folder, permutation_folder=None):
        self.snippets_folder = snippets_folder
        self.permutation_folder = permutation_folder
        validate_snippets_and_csv(snippets_folder, permutation_folder)


"""
class Cleaning:
    def __init__(self, folder_to_clean):
        self.folder_to_clean = folder_to_clean

        #think_tag_removal("generated_code", "generated_code_cleaned")
        clean_files(folder_to_clean)
"""


language = "Python"
identifier = "py"
extension = f".{identifier}"

permutations_folder = "permutations"
baseline_folder = f"generated_code/baseline_code_{identifier}"
output_folder = f"generated_code/generated_code_{identifier}"


system_prompt = f"""
    You are a code-generation assistant. You must only output complete source code in {language} language, 
    including all necessary imports and dependencies, making the output directly runnable as-is.
    Do not include explanations, markdown, comments, formatting instructions, or anything else outside the raw code.
"""


#SinglePermutationCodeGeneration()



#SetPermutationsLanguage()

#BaselineCodeGeneration()

#PermutationsCodeGeneration()

IntegrityCheck(baseline_folder)
IntegrityCheck(output_folder, permutations_folder)

#Cleaning("generated_code")
