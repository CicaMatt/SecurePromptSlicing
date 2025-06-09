import ast
import csv
import os
import re
import shutil
from collections import Counter
import pandas as pd
import warnings

warnings.filterwarnings("ignore", category=SyntaxWarning)


def add_labels(input_csv_path):
    column_labels = [
        "Name",  # Query name
        "Description",  # Query description
        "Severity",  # Severità
        "Message",  # Messaggio di avviso
        "Path",  # Percorso del file
        "StartLine",  # Riga di inizio
        "StartColumn",  # Colonna di inizio
        "EndLine",  # Riga di fine
        "EndColumn"  # Colonna di fine
    ]

    df = pd.read_csv(input_csv_path, header=None)
    df.columns = column_labels
    df.to_csv(input_csv_path, index=False)


def check_and_remove_duplicates(csv_path, remove_duplicates=False):
    try:
        # Legge il CSV in un DataFrame
        df = pd.read_csv(csv_path)

        # Trova righe duplicate (considera tutte le colonne)
        duplicates = df.duplicated(keep=False)
        num_duplicates = duplicates.sum()

        print(f"Numero di righe duplicate trovate: {num_duplicates}")

        if remove_duplicates and num_duplicates > 0:
            # Rimuove i duplicati mantenendo la prima occorrenza
            df_no_duplicates = df.drop_duplicates(keep='first')
            df_no_duplicates.to_csv(csv_path, index=False)
            print("Duplicati rimossi e file aggiornato.")

    except Exception as e:
        print(f"Errore durante l'elaborazione del file: {e}")


def add_prompt_id(csv_path: str, dataset_csv_path: str) -> None:
    """
    Modifica il CSV iniziale aggiungendo le colonne 'Prompt ID' e 'Dataset ID'
    ottenute dal mapping tramite l'ID estratto dal campo 'Path'.

    Args:
        csv_path (str): Percorso del CSV iniziale con colonna 'Path'.
        dataset_csv_path (str): Percorso del CSV contenente 'Id' e 'Prompt ID'.
    """
    # Legge il CSV iniziale
    starting_df = pd.read_csv(csv_path)

    # Estrae il numero da "permutations_"
    def extract_id(path):
        match = re.search(r'permutations_(\d+)', path)
        return int(match.group(1)) if match else None

    starting_df['Permutation_ID'] = starting_df['Path'].apply(extract_id)

    # Legge il CSV con mapping
    df_mapping = pd.read_csv(dataset_csv_path)

    # Merge per ottenere Prompt ID e Dataset ID
    starting_df = starting_df.merge(
        df_mapping[['ID', 'Prompt ID']],
        left_on='Permutation_ID',
        right_on='ID',
        how='left'
    )

    # Rinomina la colonna 'ID' in 'Dataset ID'
    starting_df.rename(columns={'ID': 'Dataset ID'}, inplace=True)

    # Rimuove la colonna temporanea
    starting_df.drop(columns=['Permutation_ID'], inplace=True)

    # Sovrascrive il CSV iniziale
    starting_df.to_csv(csv_path, index=False)


def add_cwe_id(csv_path, original_column):
    """
    Legge un file CSV, estrae la parte prima di "_" da una colonna, 
    e la salva in una nuova colonna "CWE ID". Il file CSV viene modificato direttamente.

    :param csv_path: Percorso al file CSV da modificare
    :param original_column: Nome della colonna da elaborare
    """
    # Leggi il file CSV
    df = pd.read_csv(csv_path)

    # Verifica che la colonna esista
    if original_column not in df.columns:
        raise ValueError(f"La colonna '{original_column}' non esiste nel CSV.")

    # Estrai la parte prima di "_"
    df["CWE ID"] = df[original_column].astype(str).str.split("_").str[0]

    # Sovrascrive il file CSV con le modifiche
    df.to_csv(csv_path, index=False)


def add_slicing_info(input_csv_path, lookup_dir):
    # Legge il CSV iniziale
    df = pd.read_csv(input_csv_path)

    # Controlla che la colonna "Path" esista
    if "Path" not in df.columns:
        raise ValueError("La colonna 'Path' non è presente nel CSV iniziale.")

    # Liste per memorizzare i valori estratti
    sliced_prompts = []
    original_sentences = []
    removed_parts = []
    syntagm_types = []
    granularities = []
    resulting_prompts = []
    sentence_indices = []

    for path in df["Path"]:
        try:
            parts = path.strip("/").split("/")
            if len(parts) < 2:
                sliced_prompts.append(None)
                original_sentences.append(None)
                removed_parts.append(None)
                syntagm_types.append(None)
                granularities.append(None)
                resulting_prompts.append(None)
                sentence_indices.append(None)
                continue

            csv_id = parts[0]
            row_match = re.search(r"code_row_(\d+)", parts[1])
            if not row_match:
                sliced_prompts.append(None)
                original_sentences.append(None)
                removed_parts.append(None)
                syntagm_types.append(None)
                granularities.append(None)
                resulting_prompts.append(None)
                sentence_indices.append(None)
                continue

            row_number = int(row_match.group(1))
            lookup_csv_path = os.path.join(lookup_dir, f"{csv_id}.csv")

            if not os.path.exists(lookup_csv_path):
                sliced_prompts.append(None)
                original_sentences.append(None)
                removed_parts.append(None)
                syntagm_types.append(None)
                granularities.append(None)
                resulting_prompts.append(None)
                sentence_indices.append(None)
                continue

            lookup_df = pd.read_csv(lookup_csv_path)

            if row_number < len(lookup_df):
                row = lookup_df.iloc[row_number]

                sliced_prompts.append(row.get("Final Prompt", None))
                original_sentences.append(row.get("Original Sentence", None))
                removed_parts.append(row.get("Removed Part", None))
                syntagm_types.append(row.get("Type", None))
                granularities.append(row.get("Granularity", None))
                resulting_prompts.append(row.get("Resulting Prompt", None))
                sentence_indices.append(row.get("Sentence Index", None))
            else:
                sliced_prompts.append(None)
                original_sentences.append(None)
                removed_parts.append(None)
                syntagm_types.append(None)
                granularities.append(None)
                resulting_prompts.append(None)
                sentence_indices.append(None)

        except Exception:
            sliced_prompts.append(None)
            original_sentences.append(None)
            removed_parts.append(None)
            syntagm_types.append(None)
            granularities.append(None)
            resulting_prompts.append(None)
            sentence_indices.append(None)

    # Aggiunge le colonne al DataFrame originale
    df["Sliced Prompt"] = sliced_prompts
    df["Original Sentence"] = original_sentences
    df["Removed Part"] = removed_parts
    df["Sentence Index"] = sentence_indices
    df["Syntagm Type"] = syntagm_types
    df["Granularity"] = granularities
    df["Resulting Prompt"] = resulting_prompts

    # Scrive il risultato nel file CSV
    df.to_csv(input_csv_path, index=False)


def snippets_count(folder):
    count = 0
    for root, dirs, files in os.walk(folder):
        # Escludi le directory nascoste
        dirs[:] = [d for d in dirs if not d.startswith('.')]

        # Conta solo i file visibili che non terminano con .pyc
        for file in files:
            if not file.startswith('.') and not file.endswith('.pyc'):
                file_path = os.path.join(root, file)
                if os.path.isfile(file_path):
                    count += 1
    print("Total permutations/snippets:", count)
    return count


def row_counter(csv_path):
    print("Total issues detected:", len(open(csv_path, encoding='utf-8').readlines()))


def covered_cwe_types_stats(csv_path, original_column):
    """
    Legge un file CSV, estrae la parte prima di "_" dalla colonna specificata,
    e stampa i tipi unici di CWE e il numero totale di CWE unici.

    :param csv_path: Percorso al file CSV da leggere
    :param original_column: Nome della colonna da elaborare
    """
    # Leggi il file CSV
    df = pd.read_csv(csv_path)

    # Verifica che la colonna esista
    if original_column not in df.columns:
        raise ValueError(f"La colonna '{original_column}' non esiste nel CSV.")

    # Estrai la parte prima di "_" per ogni riga
    df["CWE ID"] = df[original_column].astype(str).str.split("_").str[0]

    # Ottieni i CWE unici e ordina per ID numerico crescente
    unique_cwe = sorted(df["CWE ID"].unique(), key=lambda x: int(x.replace("CWE-", "")))

    # Stampa ciascun tipo unico di CWE
    print("Tipi unici di CWE presenti nella colonna:")
    for cwe in unique_cwe:
        print(cwe)

    # Stampa il numero totale di CWE unici
    print(f"\nNumero totale di CWE unici: {len(unique_cwe)}")


def result_cwe_stats(csv_path, cwe_column):
    """
    Legge un file CSV, analizza una colonna con valori del tipo "CWE-502",
    e stampa ciascun tipo di CWE con il numero di occorrenze, ordinati per ID crescente.

    :param csv_path: Percorso al file CSV da leggere
    :param cwe_column: Nome della colonna che contiene i valori CWE (es. "CWE-502")
    """
    # Leggi il file CSV
    df = pd.read_csv(csv_path)

    # Verifica che la colonna esista
    if cwe_column not in df.columns:
        raise ValueError(f"La colonna '{cwe_column}' non esiste nel CSV.")

    # Conta le occorrenze dei CWE
    cwe_counts = df[cwe_column].astype(str).value_counts()

    # Ordina per ID numerico crescente
    sorted_cwe_counts = cwe_counts.sort_index(key=lambda x: x.str.replace("CWE-", "").astype(int))

    # Stampa i CWE e le loro occorrenze
    print("Occorrenze di ciascun tipo di CWE:")
    for cwe, count in sorted_cwe_counts.items():
        print(f"{cwe}: {count}")

    # Stampa il numero totale di CWE unici
    print(f"\nNumero totale di CWE unici: {sorted_cwe_counts.shape[0]}")


def permutations_values_count_total(folder):
    # Inizializza contatori per ogni colonna
    type_counter = Counter()
    granularity_counter = Counter()
    sentence_index_counter = Counter()

    total_rows = 0  # Nuovo contatore per il totale delle righe

    # Scorri tutti i file nella cartella
    for filename in os.listdir(folder):
        if filename.endswith(".csv"):
            filepath = os.path.join(folder, filename)
            try:
                df = pd.read_csv(filepath)
                total_rows += len(df)  # Aggiungi il numero di righe del file

                # Aggiorna i contatori con i valori delle colonne
                if 'Type' in df.columns:
                    type_counter.update(df['Type'].dropna())
                if 'Granularity' in df.columns:
                    granularity_counter.update(df['Granularity'].dropna())
                if 'Sentence Index' in df.columns:
                    sentence_index_counter.update(df['Sentence Index'].dropna())
            except Exception as e:
                print(f"Errore nella lettura di {filename}: {e}")

    #print(f"Totale righe lette da tutti i CSV: {total_rows}\n")

    print(f" - Type: {len(type_counter)} unique values")
    for val, count in type_counter.items():
        print(f"    {val}: {count}")

    print(f" - Granularity: {len(granularity_counter)} unique values")
    for val, count in granularity_counter.items():
        print(f"    {val}: {count}")

    print(f" - Sentence Index: {len(sentence_index_counter)} unique values")
    for val, count in sentence_index_counter.items():
        print(f"    '{val}': {count}")


def analyze_snippets(filepath):
    total_files = 0
    total_txt = 0
    total_py = 0
    errors = []

    for root, dirs, files in os.walk(filepath):
        # Esclude cartelle nascoste
        dirs[:] = [d for d in dirs if not d.startswith('.')]
        for filename in files:
            if filename.startswith('.') or filename.endswith('.pyc'):
                continue

            complete_path = os.path.join(root, filename)
            total_files += 1

            if filename.endswith('.txt'):
                total_txt += 1
            elif filename.endswith('.py'):
                total_py += 1
                try:
                    with open(complete_path, 'r', encoding='utf-8') as f:
                        source = f.read()
                        ast.parse(source, filename=complete_path)
                except (SyntaxError, UnicodeDecodeError) as e:
                    errors.append((complete_path, str(e)))

    print(f"Totale file: {total_files}")
    print(f"File file .txt: {total_txt}")
    print(f"File file .py: {total_py}")
    print(f"Snippet con errori: {len(errors)}")
    print(f"Snippet corretti: {total_py - len(errors)}")
    #print(f"\nScript Python con errori di sintassi:")
    #for path, error in errors:
    #    print(f" - {path}: {error}")


def permutations_values_count_clean(csv_folder, code_folder, verbose=True):
    type_counter = Counter()
    granularity_counter = Counter()
    sentence_index_counter = Counter()

    valid_snippets = 0
    invalid_snippets = 0
    total_checked = 0
    total_txt = 0
    total_py = 0
    errors = []

    for filename in os.listdir(csv_folder):
        if not filename.endswith(".csv"):
            continue

        csv_path = os.path.join(csv_folder, filename)
        base_name = os.path.splitext(filename)[0]
        code_subfolder = os.path.join(code_folder, base_name)

        try:
            df = pd.read_csv(csv_path)
        except Exception as e:
            if verbose:
                print(f"Errore nella lettura di {filename}: {e}")
            continue

        for idx, row in df.iterrows():
            txt_path = os.path.join(code_subfolder, f"code_row_{idx}.txt")
            py_path = os.path.join(code_subfolder, f"code_row_{idx}.py")

            if os.path.exists(txt_path):
                total_txt += 1
                continue

            total_checked += 1
            total_py += 1

            if not os.path.exists(py_path):
                invalid_snippets += 1
                errors.append((py_path, "File .py mancante"))
                continue

            try:
                with open(py_path, 'r', encoding='utf-8') as code_file:
                    code = code_file.read()
                    ast.parse(code)
            except (SyntaxError, UnicodeDecodeError, FileNotFoundError) as e:
                invalid_snippets += 1
                errors.append((py_path, str(e)))
                continue

            valid_snippets += 1

            if 'Type' in df.columns:
                val = row.get('Type')
                if pd.notna(val): type_counter[val] += 1

            if 'Granularity' in df.columns:
                val = row.get('Granularity')
                if pd.notna(val): granularity_counter[val] += 1

            if 'Sentence Index' in df.columns:
                val = row.get('Sentence Index')
                if pd.notna(val): sentence_index_counter[val] += 1

    if verbose:
        print(f"Totale snippet associati a righe CSV: {total_checked + total_txt}")
        print(f"File .txt ignorati: {total_txt}")
        print(f"File .py analizzati: {total_py}")
        print(f"Snippet validi (parsabili): {valid_snippets}")
        print(f"Snippet scartati per errori: {invalid_snippets}")
        print(f"Snippet corretti: {valid_snippets}")

        print("\nStatistiche SOLO sui validi:\n")

        print(f" - Type: {len(type_counter)} valori unici")
        for val, count in type_counter.items():
            print(f"    {val}: {count}")

        print(f" - Granularity: {len(granularity_counter)} valori unici")
        for val, count in granularity_counter.items():
            print(f"    {val}: {count}")

        print(f" - Sentence Index: {len(sentence_index_counter)} valori unici")
        for val, count in sentence_index_counter.items():
            print(f"    '{val}': {count}")

    return {
        'Type': type_counter,
        'Granularity': granularity_counter,
        'Sentence Index': sentence_index_counter,
    }


def result_values_count(filepath, verbose=True):
    syntagm_type_counter = Counter()
    granularity_counter = Counter()
    sentence_index_counter = Counter()

    total_rows = 0

    try:
        df = pd.read_csv(filepath)
        total_rows = len(df)

        if 'Syntagm Type' in df.columns:
            syntagm_type_counter.update(df['Syntagm Type'].dropna())
        if 'Granularity' in df.columns:
            granularity_counter.update(df['Granularity'].dropna())
        if 'Sentence Index' in df.columns:
            sentence_index_counter.update(df['Sentence Index'].dropna())

    except Exception as e:
        if verbose:
            print(f"Errore nella lettura del file {filepath}: {e}")
        return

    if verbose:
        print(f"Totale righe lette: {total_rows}\n")

        print(f" - Syntagm Type: {len(syntagm_type_counter)} valori unici")
        for val, count in syntagm_type_counter.items():
            print(f"    {val}: {count}")

        print(f" - Granularity: {len(granularity_counter)} valori unici")
        for val, count in granularity_counter.items():
            print(f"    {val}: {count}")

        print(f" - Sentence Index: {len(sentence_index_counter)} valori unici")
        for val, count in sentence_index_counter.items():
            print(f"    '{val}': {count}")

    return {
        'Type': syntagm_type_counter,
        'Granularity': granularity_counter,
        'Sentence Index': sentence_index_counter,
    }


def compare_metric_counters(base_counters, result_counters):
    """
    base_counters: dict con chiavi 'Type', 'Granularity', 'Sentence Index' e valori Counter
    result_counters: dict con stesse chiavi e valori Counter
    """

    print("CONFRONTO TRA METRICHE (Percentuale delle seconde sulle prime)\n")

    for key in ['Type', 'Granularity', 'Sentence Index']:
        base_counter = base_counters.get(key, Counter())
        result_counter = result_counters.get(key, Counter())

        print(f"--- {key} ---")
        all_keys = set(base_counter) | set(result_counter)

        for val in sorted(all_keys):
            base_val = base_counter.get(val, 0)
            result_val = result_counter.get(val, 0)

            if base_val == 0:
                percent = "N/A (non presente nei base)"
            else:
                percent = f"{(result_val / base_val) * 100:.2f}%"

            print(f"  {val}: {result_val} / {base_val} → {percent}")
        print("\n")



##################################################################################################################


prompt_dataset = 'LLMSecEvalDataset.csv'
result_py = 'results_codeql/results_py.csv'
result_py_complete = 'results_codeql/results_py_complete.csv'
snippets_folder = 'generated_code'
permutations_folder = 'permutations'


class CsvBuilder:
    def __init__(self):
        shutil.copy(result_py, result_py_complete)
        add_labels(result_py_complete)
        add_prompt_id(result_py_complete, prompt_dataset)
        add_cwe_id(result_py_complete, "Prompt ID")
        add_slicing_info(result_py_complete, permutations_folder)
        #check_and_remove_duplicates(result_py_complete, remove_duplicates=False)


class PermutationsStats:
    def __init__(self):
        print("Permutations Stats - All")
        permutations_values_count_total(permutations_folder)
        #analyze_snippets(snippets_folder)
        print("\n---------------------------------------")
        print("\nPermutations Stats - Correct Snippets:")
        permutations_values_count_clean(permutations_folder, snippets_folder)


class ResultStats:
    def __init__(self):
        #snippets_count(snippets_folder)
        #row_counter(result_py_complete)
        print("Baseline CWEs Stats:")
        covered_cwe_types_stats(prompt_dataset, "Prompt ID")
        print("\n---------------------------------------")
        print("\nAnalysis CWEs Stats:")
        result_cwe_stats(result_py_complete, "CWE ID")
        print("\n---------------------------------------")
        print("\nResult Stats:")
        result_values_count(result_py_complete)


class MetricsComparison:
    def __init__(self):
        print("\nPermutations Stats - Correct Snippets:")
        base_values = permutations_values_count_clean(permutations_folder, snippets_folder)
        print("\n---------------------------------------")
        print("\nResult Stats:")
        result_values = result_values_count(result_py_complete)
        print("\n---------------------------------------")
        print("\nParameters Comparison Stats:")
        compare_metric_counters(base_values, result_values)


CsvBuilder()
#PermutationsStats()
#ResultStats()
MetricsComparison()