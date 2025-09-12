import ast
import csv
import importlib
import os
import shutil
import subprocess
import sys
import tempfile
import tokenize
from collections import defaultdict
from pathlib import Path
from typing import Tuple, List, Iterable

import pandas as pd
import requests
import time
import re

import warnings
#warnings.filterwarnings("ignore", category=SyntaxWarning)


# === Settings ===
LM_STUDIO_ENDPOINT = "http://localhost:1235/v1/chat/completions"  # Set to your LM Studio endpoint
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
        "model": model_identifier,
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



def looks_like_code(line):
    line = line.strip()

    # ❌ Se è un comando terminale, NON è codice
    if re.match(r'^(javac|java|python[0-9]*|pip|curl|wget|make|bash|sh|node|npm)\b', line):
        return False

    # ✅ Condizioni per cui lo consideriamo codice
    return (
        line.startswith("#include") or
        line.startswith("def ") or
        line.startswith("class ") or
        line.startswith("import ") or
        line.endswith(";") or
        re.match(r'\w+\s*\(.*\)\s*{?', line) or
        line.startswith("if ") or
        line.startswith("for ") or
        line.startswith("while ") or
        line.startswith("return ")
    )

def find_trailing_comments(base_path, extensions=None, remove=False):
    total_found = 0
    total_removed = 0

    for root, _, files in os.walk(base_path):
        for file in files:
            if extensions is None or any(file.endswith(ext) for ext in extensions):
                file_path = os.path.join(root, file)
                try:
                    with open(file_path, "r", encoding="utf-8", errors="ignore") as f:
                        lines = f.readlines()

                    new_lines = []
                    in_block = False
                    current_block = []
                    keep_block = False
                    removed_blocks_in_file = 0

                    for line in lines:
                        stripped = line.strip()

                        if stripped.startswith("###"):
                            if in_block:
                                if not keep_block:
                                    removed_blocks_in_file += 1
                                    total_removed += 1
                                else:
                                    # ✅ Tieni solo il contenuto, rimuovi intestazione "### ..."
                                    new_lines.extend(current_block[1:])

                            in_block = True
                            current_block = [line]
                            keep_block = False  # azzera e valuta nel blocco
                        elif in_block:
                            current_block.append(line)
                            if looks_like_code(line):
                                keep_block = True
                        else:
                            new_lines.append(line)

                    # Gestione blocco finale (se presente)
                    if in_block:
                        if keep_block:
                            new_lines.extend(current_block[1:])
                        else:
                            removed_blocks_in_file += 1
                            total_removed += 1

                    if removed_blocks_in_file > 0:
                        total_found += 1
                        print(f"\n🗑️ Pulito {removed_blocks_in_file} blocco/i da: {file_path}")

                    if remove and (removed_blocks_in_file > 0 or in_block):
                        with open(file_path, "w", encoding="utf-8") as f_out:
                            f_out.writelines(new_lines)

                except Exception as e:
                    print(f"❌ Errore su {file_path}: {e}")

    print(f"\n✅ File con blocchi rimossi: {total_found}")
    print(f"🧹 Totale blocchi rimossi: {total_removed}")



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


def count_files_with_extension(folder, extension):
    """
    Recursively counts all non-hidden files with a given extension within a folder.

    Args:
        folder (str): Path to the starting folder.
        extension (str): File extension to look for (e.g., ".txt").

    Returns:
        int: Number of matching files.
    """
    count = 0
    for root, dirs, files in os.walk(folder):
        # Skip hidden directories
        dirs[:] = [d for d in dirs if not d.startswith('.')]
        for file in files:
            if not file.startswith('.') and file.endswith(extension):
                count += 1

    print("Total number of files with extension '{extension}': {count}".format(extension=extension, count=count))
    return count



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


class SampledBaselineCodeGeneration:
    def __init__(self):
        os.makedirs(samples_baseline_code, exist_ok=True)
        # === Main processing ===
        with open(samples_baseline_csv, newline='', encoding='utf-8') as csvfile:
            reader = csv.DictReader(csvfile)
            for i, row in enumerate(reader):
                prompt = row["Manually-fixed NL Prompt"]

                # Sostituzione del placeholder <language> con "Python"
                prompt = prompt.replace("<language>", language)

                ext = extension  # Estensione di default
                filename = f"code_row_{i + 1}{ext}"
                filepath = os.path.join(samples_baseline_code, filename)

                try:
                    print(f"▶️ Generating code for row {i + 1}...")
                    code = call_lmstudio(prompt)
                    with open(filepath, "w", encoding="utf-8") as f:
                        f.write(code)
                    print(f"✅ Saved to {filepath}")
                    time.sleep(SLEEP_BETWEEN_REQUESTS)
                except Exception as e:
                    print(f"❌ Error generating code for row {i + 1}: {e}")

"""
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
"""

class PermutationsCodeGeneration:
    def __init__(self, skip_existing=False):
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
                        prompt_template = row["Resulting Prompt"]
                        prompt = prompt_template.replace("<language>", language)

                        ext = extension
                        filename_out = f"code_row_{i+1}{ext}"
                        filepath = os.path.join(output_subfolder, filename_out)

                        # Salta se già esiste e modalità attiva
                        if skip_existing and os.path.exists(filepath):
                            print(f"⏭️ Snippet già esistente: {filepath}, salto.")
                            continue

                        try:
                            print(f"▶️ Generating code for row {i+1} in {os.path.basename(csv_path)}...")
                            code = call_lmstudio(prompt)
                            with open(filepath, "w", encoding="utf-8") as f:
                                f.write(code)
                            print(f"✅ Saved to {filepath}")
                            time.sleep(SLEEP_BETWEEN_REQUESTS)
                        except Exception as e:
                            print(f"❌ Error generating code for row {i+1}: {e}")


class SampledPermutationsCodeGeneration:
    def __init__(self, skip_existing=False):
        os.makedirs(samples_permutations_folder, exist_ok=True)
        # Itera su tutti i file CSV nella cartella di input
        for filename in os.listdir(samples_permutations_folder):
            if filename.endswith(".csv"):
                csv_path = os.path.join(samples_permutations_folder, filename)
                csv_name_no_ext = os.path.splitext(filename)[0]

                # Crea sottocartella di output
                output_subfolder = os.path.join(samples_permutations_code, csv_name_no_ext)
                os.makedirs(output_subfolder, exist_ok=True)

                # Inizia la logica di elaborazione CSV qui
                with open(csv_path, newline='', encoding='utf-8') as csvfile:
                    reader = csv.DictReader(csvfile)
                    for i, row in enumerate(reader):
                        prompt_template = row["Resulting Prompt"]
                        prompt = prompt_template.replace("<language>", language)

                        ext = extension
                        filename_out = f"code_row_{i+1}{ext}"
                        filepath = os.path.join(output_subfolder, filename_out)

                        # Salta se già esiste e modalità attiva
                        if skip_existing and os.path.exists(filepath):
                            print(f"⏭️ Snippet già esistente: {filepath}, salto.")
                            continue

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
        count_files_with_extension(snippets_folder, extension)
        count_empty_files(snippets_folder, extension)
        find_trailing_comments(snippets_folder, extension, remove=False)
        count_wrong_extension(snippets_folder, extension)
        validate_snippets_and_csv(snippets_folder, permutation_folder)
        print("\n----------------------------------------------------------------\n")


class Cleaning:
    def __init__(self, snippets_folder):
        self.folder_to_clean = snippets_folder
        change_file_extensions(snippets_folder, extension)
        #find_trailing_comments(snippets_folder, extension, remove=True)
        #find_llm_comments(folder_to_clean, extension, remove=True)



#model_identifier = "qwen2.5-coder-32b-instruct"
model_identifier = "athene-v2-chat"
#model_identifier = "phi-4"


model_name = "athene"
sample_folder_id = 3

language = "C"
identifier = "c"
extension = f".{identifier}"


permutations_folder = "permutations"
baseline_folder = f"generated_code/{model_name}/baseline_code_{identifier}"
output_folder = f"generated_code/{model_name}/generated_code_{identifier}"

samples_baseline_csv = f"samples/baseline_sample_{sample_folder_id}.csv"
samples_permutations_folder = f"samples/permutations_sample_{sample_folder_id}"
samples_baseline_code = f"samples_generated_code/samples_{sample_folder_id}/{model_name}/baseline_code_{identifier}"
samples_permutations_code = f"samples_generated_code/samples_{sample_folder_id}/{model_name}/generated_code_{identifier}"


system_prompt = f"""
    You are a code-generation assistant. You must only output complete source code in {language} language, 
    including all necessary imports and dependencies, making the output directly runnable as-is.
    Do not include explanations, markdown, comments, or anything else outside the raw code.
"""



#BaselineCodeGeneration()

#PermutationsCodeGeneration(skip_existing=True)

#IntegrityCheck(baseline_folder)
#IntegrityCheck(output_folder, permutations_folder)

#SampledBaselineCodeGeneration()
#SampledPermutationsCodeGeneration()



#Cleaning(baseline_folder)
#Cleaning(output_folder)