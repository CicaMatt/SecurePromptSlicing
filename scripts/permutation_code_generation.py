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


def organize_java_snippets(base_path=None, output_path=None):
    if os.path.exists(output_path) and os.path.isdir(output_path):
        shutil.rmtree(output_path)

    if base_path is None:
        base_path = Path.cwd()
    else:
        base_path = Path(base_path)

    if output_path is None:
        raise ValueError("È necessario specificare un 'output_path'.")
    output_path = Path(output_path)
    output_path.mkdir(parents=True, exist_ok=True)

    aggregators_created = set()

    for java_file in base_path.rglob("*.java"):
        relative_path = java_file.relative_to(base_path).parent
        basename = java_file.stem

        # Genera un nome univoco per il modulo usando il percorso + nome file
        module_name = f"{relative_path.as_posix().replace('/', '-')}-{basename}" if relative_path.parts else basename

        # Nuova directory con struttura relativa
        new_dir = output_path / relative_path / basename
        dest_dir = new_dir / "src/main/java"

        print(f"Elaboro: {java_file} -> {dest_dir}")

        # Crea la struttura
        dest_dir.mkdir(parents=True, exist_ok=True)
        shutil.copy2(java_file, dest_dir / java_file.name)

        # Crea pom.xml del modulo
        module_pom = new_dir / "pom.xml"
        pom_content = f'''<project xmlns="http://maven.apache.org/POM/4.0.0"
         xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
         xsi:schemaLocation="http://maven.apache.org/POM/4.0.0 
                             http://maven.apache.org/xsd/maven-4.0.0.xsd">
  <modelVersion>4.0.0</modelVersion>
  <parent>
    <groupId>com.example</groupId>
    <artifactId>{new_dir.parent.name}-parent</artifactId>
    <version>1.0.0</version>
  </parent>
  <artifactId>{module_name}</artifactId>
</project>'''
        module_pom.write_text(pom_content)

        # Crea POM aggregatore nella cartella superiore, se non già creato
        aggregator_dir = new_dir.parent
        aggregator_pom = aggregator_dir / "pom.xml"
        if aggregator_dir not in aggregators_created:
            aggregator_artifact_id = f"{aggregator_dir.name}-parent"
            aggregator_content = f'''<project xmlns="http://maven.apache.org/POM/4.0.0"
         xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
         xsi:schemaLocation="http://maven.apache.org/POM/4.0.0 
                             http://maven.apache.org/xsd/maven-4.0.0.xsd">
  <modelVersion>4.0.0</modelVersion>
  <groupId>com.example</groupId>
  <artifactId>{aggregator_artifact_id}</artifactId>
  <version>1.0.0</version>
  <packaging>pom</packaging>
  <modules>
    <module>{basename}</module>
  </modules>
</project>'''
            aggregator_pom.write_text(aggregator_content)
            aggregators_created.add(aggregator_dir)
        else:
            # Aggiungi il modulo se già esiste il pom aggregatore
            text = aggregator_pom.read_text()
            if f"<module>{basename}</module>" not in text:
                text = text.replace("</modules>", f"    <module>{basename}</module>\n  </modules>")
                aggregator_pom.write_text(text)

    # === CREA POM AGGREGATORE GLOBALE ===
    global_modules = [str(p.relative_to(output_path)) for p in aggregators_created]

    global_pom_content = f'''<project xmlns="http://maven.apache.org/POM/4.0.0"
     xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
     xsi:schemaLocation="http://maven.apache.org/POM/4.0.0 
                         http://maven.apache.org/xsd/maven-4.0.0.xsd">
  <modelVersion>4.0.0</modelVersion>
  <groupId>com.example</groupId>
  <artifactId>aggregator-root</artifactId>
  <version>1.0.0</version>
  <packaging>pom</packaging>
  <modules>
'''

    for module_path in sorted(global_modules):
        global_pom_content += f"    <module>{module_path}</module>\n"

    global_pom_content += '''  </modules>
</project>'''

    (output_path / "pom.xml").write_text(global_pom_content)


def rename_java_files(folder, wrap_if_no_class=True):
    """
    Scansiona ricorsivamente la cartella, cerca i file .java,
    estrae il nome della prima classe e rinomina il file di conseguenza,
    evitando nomi duplicati.

    Se `wrap_if_no_class` è True e non viene trovata alcuna classe,
    incapsula il contenuto in una classe generica.
    """
    used_class_names = set()

    for root, _, files in os.walk(folder):
        for filename in files:
            if filename.endswith(".java"):
                complete_path = os.path.join(root, filename)
                with open(complete_path, 'r', encoding='utf-8', errors='ignore') as f:
                    content = f.read()

                match = re.search(r'\bclass\s+(\w+)', content)
                if match:
                    original_class_name = match.group(1)
                elif wrap_if_no_class:
                    # Genera nome classe generica da nome file
                    original_class_name = os.path.splitext(filename)[0].capitalize() + "Wrapper"
                    content = f"public class {original_class_name} {{\n{content}\n}}"
                    with open(complete_path, 'w', encoding='utf-8') as f:
                        f.write(content)
                    print(f"Nessuna classe trovata in: {filename}, incapsulato in classe {original_class_name}.")
                else:
                    print(f"Saltato: {filename} (nessuna classe trovata e wrapping disabilitato).")
                    continue  # Salta il file

                # Evita nomi duplicati
                class_name = original_class_name
                counter = 1
                while class_name in used_class_names:
                    class_name = f"{original_class_name}_{counter}"
                    counter += 1

                used_class_names.add(class_name)

                # Se il nome è stato modificato, aggiorna anche il contenuto della classe
                if class_name != original_class_name:
                    content = re.sub(r'\bclass\s+' + re.escape(original_class_name), f'class {class_name}', content)
                    with open(complete_path, 'w', encoding='utf-8') as f:
                        f.write(content)
                    print(f"Classe {original_class_name} rinominata in {class_name} per evitare duplicati.")

                new_name = class_name + ".java"
                new_path = os.path.join(root, new_name)
                if new_path != complete_path:
                    print(f"Rinomino: {filename} -> {new_name}")
                    os.rename(complete_path, new_path)


def duplication_removal(base_dir):
    class_name_counts = defaultdict(int)
    renamed_classes = {}

    # Step 1: raccogli tutte le classi (anche non pubbliche)
    java_files = []
    class_pattern = re.compile(r'\b(class|interface|enum)\s+(\w+)')

    for root, _, files in os.walk(base_dir):
        for file in files:
            if file.endswith(".java"):
                full_path = os.path.join(root, file)
                java_files.append(full_path)

    for path in java_files:
        with open(path, 'r', encoding='utf-8') as f:
            content = f.read()

        for match in class_pattern.finditer(content):
            class_name = match.group(2)
            class_name_counts[class_name] += 1

    # Step 2: rinomina classi duplicate
    for path in java_files:
        with open(path, 'r', encoding='utf-8') as f:
            content = f.read()

        modified = False
        new_content = content

        for match in class_pattern.finditer(content):
            keyword, old_name = match.groups()
            if class_name_counts[old_name] > 1:
                base = old_name
                i = 1
                while True:
                    new_name = f"{base}_{i}"
                    if new_name not in class_name_counts:
                        break
                    i += 1

                new_content = re.sub(rf'\b{keyword}\s+{old_name}\b',
                                     f'{keyword} {new_name}', new_content)
                class_name_counts[new_name] = 1
                renamed_classes[old_name] = new_name
                modified = True

                # rinomina anche il file se il nome file coincide con la classe
                file_name = os.path.basename(path)
                if file_name == f"{old_name}.java":
                    new_file_name = os.path.join(os.path.dirname(path), f"{new_name}.java")
                    os.rename(path, new_file_name)
                    path = new_file_name  # aggiorna per evitare future collisioni
                    break

        if modified:
            with open(path, 'w', encoding='utf-8') as f:
                f.write(new_content)

    return renamed_classes


def find_errors_java(folder):
    errors = {}

    for root, _, files in os.walk(folder):
        for file in files:
            if file.endswith(".java"):
                filepath = os.path.join(root, file)
                try:
                    result = subprocess.run(
                        ["javac", filepath],
                        capture_output=True,
                        text=True
                    )
                    if result.returncode != 0:
                        errors[filepath] = result.stderr.strip()
                except FileNotFoundError:
                    print("Errore: javac non trovato. Assicurati che Java sia installato e presente nel PATH.")
                    return None

    if errors:
        print("\n=== File con errors sintattici ===")
        for idx, (file, message) in enumerate(sorted(errors.items()), start=1):
            print(f"{idx}. {file}")
            print(f"   → Errore: {message.splitlines()[0]}\n")  # stampa solo la prima riga dell'errore

        print(f"Totale file non validi: {len(errors)}")
    else:
        print("Tutti i file .java sono sintatticamente corretti.")

    return errors



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
                        prompt_template = row["Resulting prompt"]
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


class Cleaning:
    def __init__(self, folder_to_clean):
        self.folder_to_clean = folder_to_clean

        #think_tag_removal("generated_code", "generated_code_cleaned")
        clean_files(folder_to_clean)


class JavaPreprocessing:
    def __init__(self):
        # Struttura la cartella con i vari pom.xml
        organize_java_snippets(output_folder, )
        # Scansiona ricorsivamente i file .java, estrae il nome della prima classe e rinomina il file di conseguenza evitando nomi duplicati
        #rename_java_files(output_folder)
        find_errors_java(output_folder)



language = "C"
extension = ".c"

baseline_folder = "baseline_code_" + language.lower()
output_folder = "generated_code_" + language.lower()
output_folder_formatted = "generated_code_" + language.lower() + "_formatted"
permutations_folder = "permutations"


system_prompt = """
    You are a code-generation assistant. You must only output complete source code in """ + language + """ language, 
    including all necessary imports and dependencies, making the output directly runnable as-is.
    Do not include explanations, markdown, comments, formatting instructions, or anything else outside the raw code.
"""


#SetPermutationsLanguage()


#SinglePermutationCodeGeneration()


BaselineCodeGeneration()


PermutationsCodeGeneration()
#Cleaning("generated_code")
