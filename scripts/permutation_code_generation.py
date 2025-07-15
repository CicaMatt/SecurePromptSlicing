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


def validate_snippets_and_csv(snippet_folder, csv_folder=None):
    """
    Validates the consistency between a snippet folder and a corresponding CSV folder:
    - If `snippet_folder` contains files directly, checks that there are exactly 150 visible files (ignores hidden files).
    - If it contains subfolders, for each subfolder:
        - Counts the number of visible snippet files inside it.
        - Looks for a CSV file in `csv_folder` with the same name as the subfolder.
        - Verifies that the number of data rows in the CSV (excluding the header) matches the number of snippet files.
        - At the end, prints the number of subfolders analyzed and the total number of mismatches or missing elements.
    """
    entries = [e for e in os.listdir(snippet_folder) if not e.startswith('.')]
    entry_paths = [os.path.join(snippet_folder, e) for e in entries]
    total_missing_or_mismatched = 0

    if all(os.path.isfile(p) for p in entry_paths):
        # Case 1: folder contains snippets directly
        snippet_files = [p for p in entry_paths if os.path.isfile(p) and not os.path.basename(p).startswith('.')]
        if len(snippet_files) == 150:
            print("OK: Exactly 150 snippet files found.")
        else:
            print(f"ERROR: Expected 150 snippet files, found {len(snippet_files)}.")
            total_missing_or_mismatched += abs(150 - len(snippet_files))
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
                    total_missing_or_mismatched += snippet_count
                    continue

                with open(csv_path, newline='', encoding='utf-8') as csvfile:
                    reader = csv.reader(csvfile)
                    next(reader, None)  # Skip header row
                    csv_row_count = sum(1 for _ in reader)

                if snippet_count != csv_row_count:
                    diff = abs(snippet_count - csv_row_count)
                    print(
                        f"MISMATCH: '{entry}': {snippet_count} snippets vs {csv_row_count} CSV rows (excluding header).")
                    total_missing_or_mismatched += diff
                else:
                    print(f"OK: '{entry}' has {snippet_count} snippets and {csv_row_count} data rows in CSV.")

        print(f"\nTotal subfolders analyzed: {folder_count}")

    print(f"Total missing or mismatched snippets: {total_missing_or_mismatched}")
        

def count_wrong_extension(folder, target_extension):
    """
    Recursively counts visible files that do NOT have the specified extension,
    and prints the different extensions found along with their counts.

    :param folder: Path to the starting folder
    :param target_extension: Extension to exclude (e.g., '.txt')
    :return: Total number of files with a different extension
    """
    if not target_extension.startswith('.'):
        target_extension = '.' + target_extension
    target_extension = target_extension.lower()

    count = 0
    extension_counts = defaultdict(int)

    for root, _, files in os.walk(folder):
        for file in files:
            if file.startswith('.'):
                continue  # Skip hidden files

            ext = os.path.splitext(file)[1].lower()
            if ext != target_extension:
                key = ext if ext else '[no extension]'
                extension_counts[key] += 1
                count += 1

    if count > 0:
        print(f"Files with different extensions (excluding '{target_extension}'):")
        for ext, ext_count in sorted(extension_counts.items()):
            print(f"  {ext}: {ext_count}")

    print(f"Total files with different extension: {count}")
    return count


def count_empty_files(directory, extension):
    """
    Recursively analyzes a directory and counts the empty files
    with a specific extension.

    Args:
        directory (str): The path of the directory to analyze.
        extension (str): The file extension to consider (e.g., ".txt").

    Returns:
        int: The number of empty files found.
    """
    count = 0
    for root, dirs, files in os.walk(directory):
        for file in files:
            if file.endswith(extension):
                file_path = os.path.join(root, file)
                if os.path.getsize(file_path) == 0:
                    count += 1
    print(f"Number of empty files with extension '{extension}': {count}")
    return count


def find_llm_comments(base_path, extensions, remove=False, print_found=False):
    explanations = []
    count = 0

    # Pattern che rileva sia "### Explanation:" che "### Response:"
    pattern = re.compile(r"### (Explanation|Response):")

    for root, _, files in os.walk(base_path):
        for file in files:
            if any(file.endswith(ext) for ext in extensions):
                file_path = os.path.join(root, file)
                try:
                    with open(file_path, 'r', encoding='utf-8', errors='ignore') as f:
                        content = f.read()

                    match = pattern.search(content)
                    if match:
                        count += 1
                        start_idx = match.start()
                        explanation = content[start_idx:]
                        explanations.append((file_path, explanation.strip()))

                        if print_found:
                            print(f"\n{file_path}:\n{explanation.strip()}\n")

                        if remove:
                            new_content = content[:start_idx].rstrip() + "\n"
                            with open(file_path, 'w', encoding='utf-8') as f_out:
                                f_out.write(new_content)

                except Exception as e:
                    print(f"Could not process file {file_path}: {e}")

    print(f"Total comments found: {count}")
    return explanations


def change_file_extensions(base_folder, correct_extension):
    """
    Recursively scans all non-hidden files in the given base_folder.
    If a file does not have the correct extension, it renames it to have the correct one.

    Args:
        base_folder (str): Path to the folder to scan.
        correct_extension (str): Desired file extension, e.g., '.txt'.
    """
    if not correct_extension.startswith('.'):
        correct_extension = '.' + correct_extension

    for root, _, files in os.walk(base_folder):
        # Skip hidden folders
        if any(part.startswith('.') for part in root.split(os.sep)):
            continue

        for filename in files:
            # Skip hidden files
            if filename.startswith('.'):
                continue

            full_path = os.path.join(root, filename)
            name, current_extension = os.path.splitext(filename)

            if current_extension.lower() != correct_extension.lower():
                new_filename = name + correct_extension
                new_path = os.path.join(root, new_filename)
                print(f"Renaming: {full_path} -> {new_path}")
                os.rename(full_path, new_path)


###################################################################################################################



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

                ext = extension  # Estensione di default
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
                ext = extension
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

                        ext = extension  # estensione di default
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
        count_empty_files(snippets_folder, extension)
        find_llm_comments(snippets_folder, extension)
        count_wrong_extension(snippets_folder, extension)
        validate_snippets_and_csv(snippets_folder, permutation_folder)
        print("\n----------------------------------------------------------------\n")



class Cleaning:
    def __init__(self, folder_to_clean):
        self.folder_to_clean = folder_to_clean
        change_file_extensions(folder_to_clean, extension)
        find_llm_comments(folder_to_clean, extension, remove=True)




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



#BaselineCodeGeneration()

#PermutationsCodeGeneration()

IntegrityCheck(baseline_folder)
IntegrityCheck(output_folder, permutations_folder)

Cleaning(baseline_folder)
Cleaning(output_folder)
