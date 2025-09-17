import ast
import csv
import json
import os
import re
import shutil
import traceback
import urllib
from collections import Counter
from itertools import combinations
from typing import Dict, Set

import numpy as np
import pandas as pd
import warnings
import matplotlib.pyplot as plt
from dask.delayed import single_key
from scipy.stats import chi2_contingency, mannwhitneyu, fisher_exact
from sklearn.compose import ColumnTransformer
from sklearn.linear_model import LogisticRegression
from sklearn.metrics import classification_report, confusion_matrix
from sklearn.model_selection import train_test_split
from sklearn.pipeline import make_pipeline
from sklearn.preprocessing import MultiLabelBinarizer, OneHotEncoder
import seaborn as sns



def add_labels(input_csv_path):
    column_labels = [
        "Name",         # Query name
        "Description",  # Query description
        "Severity",     # Severità
        "Message",      # Messaggio di avviso
        "Path",         # Percorso del file
        "StartLine",    # Riga di inizio
        "StartColumn",  # Colonna di inizio
        "EndLine",      # Riga di fine
        "EndColumn"     # Colonna di fine
    ]

    if os.path.getsize(input_csv_path) == 0:
        # If the file is empty, just write the headers
        pd.DataFrame(columns=column_labels).to_csv(input_csv_path, index=False)
    else:
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


def add_prompt_id(csv_path: str, dataset_csv_path: str, mode: str = 'Results') -> None:
    """
    Modifica il CSV iniziale aggiungendo le colonne 'Prompt ID' e 'Dataset ID'
    ottenute dal mapping tramite l'ID estratto dal campo 'Path'.

    Args:
        csv_path (str): Percorso del CSV iniziale con colonna 'Path'.
        dataset_csv_path (str): Percorso del CSV contenente 'Id' e 'Prompt ID'.
        mode: Aggiunta per la baseline o per i risultati ('Results' o 'Baseline').
    """
    # Legge il CSV iniziale
    starting_df = pd.read_csv(csv_path)

    # Estrae il numero da "permutations_" o "row_"
    def extract_id(path):
        if mode == 'Results':
            match = re.search(r'permutations_(\d+)', path)
            return int(match.group(1)) if match else None
        elif mode == 'Baseline':
            match = re.search(r'row_(\d+)', path)
            return int(match.group(1)) if match else None

    starting_df['Permutation_ID'] = starting_df['Path'].apply(extract_id)

    # Converte Permutation_ID in intero
    starting_df['Permutation_ID'] = pd.to_numeric(starting_df['Permutation_ID'], errors='coerce')

    # Legge il CSV con mapping
    df_mapping = pd.read_csv(dataset_csv_path)

    # Converte ID in intero
    df_mapping['ID'] = pd.to_numeric(df_mapping['ID'], errors='coerce')

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


def add_slicing_info(input_csv_path, lookup_dir, language):
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

            row_number = int(row_match.group(1)) # Questo è 1-based
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

            # --- BLOCCO MODIFICATO ---
            # Converte il numero di riga (1-based) in un indice per pandas (0-based)
            zero_based_index = row_number - 1

            # Controlla che l'indice calcolato sia valido per il DataFrame
            if 0 <= zero_based_index < len(lookup_df):
                row = lookup_df.iloc[zero_based_index] # Usa l'indice corretto

                resulting_prompt = row.get("Resulting Prompt", None)
                if pd.notna(resulting_prompt):
                    replaced_prompt = resulting_prompt.replace("<language>", language)
                else:
                    replaced_prompt = None

                sliced_prompts.append(replaced_prompt)
                original_sentences.append(row.get("Original Sentence", None))
                removed_parts.append(row.get("Removed Part", None))
                syntagm_types.append(row.get("Type", None))
                granularities.append(row.get("Granularity", None))
                resulting_prompts.append(resulting_prompt)
                sentence_indices.append(row.get("Sentence Index", None))
            # --- FINE BLOCCO MODIFICATO ---
            else:
                # La riga richiesta è fuori dai limiti del file CSV
                sliced_prompts.append(None)
                original_sentences.append(None)
                removed_parts.append(None)
                syntagm_types.append(None)
                granularities.append(None)
                resulting_prompts.append(None)
                sentence_indices.append(None)

        except Exception:
            # Gestione generica di altri errori (es. file malformato)
            sliced_prompts.append(None)
            original_sentences.append(None)
            removed_parts.append(None)
            syntagm_types.append(None)
            granularities.append(None)
            resulting_prompts.append(None)
            sentence_indices.append(None)

    # Aggiunge le nuove colonne al DataFrame originale
    df["Sliced Prompt"] = sliced_prompts
    df["Original Sentence"] = original_sentences
    df["Removed Part"] = removed_parts
    df["Sentence Index"] = sentence_indices
    df["Syntagm Type"] = syntagm_types
    df["Granularity"] = granularities
    df["Resulting Prompt"] = resulting_prompts

    # Scrive il risultato nel file CSV di input
    df.to_csv(input_csv_path, index=False)


def add_prompt_info(csv1_path, csv2_path):
    # Leggi i CSV
    df1 = pd.read_csv(csv1_path)
    df2 = pd.read_csv(csv2_path)

    # Verifica colonne richieste
    if 'Dataset ID' not in df1.columns or 'ID' not in df2.columns or 'Manually-fixed NL Prompt' not in df2.columns:
        raise ValueError("CSV1 deve avere 'Dataset ID'; CSV2 deve avere 'ID' e 'Manually-fixed NL Prompt'.")

    # Crea dizionario: ID → Prompt
    id_to_prompt = dict(zip(df2['ID'], df2['Manually-fixed NL Prompt']))

    # Aggiungi la colonna 'Prompt' a df1 (nome desiderato)
    df1['Prompt'] = df1['Dataset ID'].map(id_to_prompt)

    # Sovrascrivi il file originale
    df1.to_csv(csv1_path, index=False)


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
    print(len(open(csv_path, encoding='utf-8').readlines()))


def count_files_by_extension(folder, extension):
    """
    Recursively counts the number of files with a given extension in a folder.

    Args:
        folder (str): The path to the folder to analyze.
        extension (str): The file extension to look for (e.g., '.txt').

    Returns:
        int: Total number of files with the specified extension.
    """
    count = 0
    extension = extension.lower()

    for root, _, files in os.walk(folder):
        for file in files:
            if file.lower().endswith(extension):
                count += 1

    print(count)
    return count


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
    #print("Tipi unici di CWE presenti nella colonna:")
    for cwe in unique_cwe:
        print(cwe)

    # Stampa il numero totale di CWE unici
    print(f"\nUnique CWEs: {len(unique_cwe)}")


def cwe_stats(csv_path, cwe_column, verbose=True):
    """
    Legge un file CSV, analizza una colonna con valori del tipo "CWE-502",
    e restituisce un dizionario con il numero di occorrenze per ciascun CWE,
    ordinati per ID crescente.

    :param csv_path: Percorso al file CSV da leggere
    :param cwe_column: Nome della colonna che contiene i valori CWE (es. "CWE-502")
    :param verbose: Se True, stampa i risultati a video
    :return: Dizionario con le occorrenze di ciascun CWE
    """
    try:
        df = pd.read_csv(csv_path)

        if cwe_column not in df.columns:
            raise ValueError(f"La colonna '{cwe_column}' non esiste nel CSV.")

        # Conta le occorrenze dei CWE
        cwe_counts = Counter(df[cwe_column].dropna().astype(str))

        # Ordina per ID numerico (es. "CWE-502" -> 502)
        sorted_cwe_counts = dict(sorted(
            cwe_counts.items(),
            key=lambda x: int(x[0].replace("CWE-", "")) if x[0].startswith("CWE-") else float('inf')
        ))

        if verbose:
            #print(f"Totale righe lette: {len(df)}\n")
            print(f" - {cwe_column}: {len(sorted_cwe_counts)} valori unici")
            for cwe, count in sorted_cwe_counts.items():
                print(f"    {cwe}: {count}")

        return {cwe_column: Counter(sorted_cwe_counts)}

    except Exception as e:
        if verbose:
            print(f"Errore nella lettura del file {csv_path}: {e}")
        return

r"""
def permutations_cwe_stats(main_csv_path, prompt_id_column, permutations_folder):
    # Version that works without the added labels in the permutations csvs
    def extract_cwe(prompt_id):
        match = re.search(r'CWE-\d+', str(prompt_id))
        return match.group(0) if match else None

    df_main = pd.read_csv(main_csv_path)

    if prompt_id_column not in df_main.columns:
        raise ValueError(f"Column '{prompt_id_column}' not found in the CSV.")

    # Conta le varianti iniziali per ciascun CWE
    df_main['CWE_ID'] = df_main[prompt_id_column].apply(extract_cwe)
    cwe_variant_counts = df_main['CWE_ID'].value_counts().sort_index(key=lambda x: x.str.replace("CWE-", "").astype(int))

    print("Numero di varianti iniziali per ciascun CWE-ID:")
    for cwe, count in cwe_variant_counts.items():
        print(f"{cwe}: {count}")
    print()

    # Aggrega le occorrenze totali nei file delle permutazioni
    all_cwes = []

    for index, row in df_main.iterrows():
        cwe_id = row['CWE_ID']
        if not cwe_id:
            continue

        file_index = index + 1  # Adjust index to start from 1
        file_path = os.path.join(permutations_folder, f"syntactic_permutations_{file_index}.csv")

        if os.path.exists(file_path):
            try:
                df_perm = pd.read_csv(file_path)
                all_cwes.extend([cwe_id] * len(df_perm))
            except Exception as e:
                print(f"Error reading {file_path}: {e}")
        else:
            print(f"File not found: {file_path}")

    # Conta e ordina le occorrenze
    cwe_series = pd.Series(all_cwes)
    cwe_counts = cwe_series.value_counts()
    sorted_cwe_counts = cwe_counts.sort_index(key=lambda x: x.str.replace("CWE-", "").astype(int))

    # Stampa i risultati
    print("Occorrenze totali (dalle permutazioni) per ciascun CWE-ID:")
    for cwe, count in sorted_cwe_counts.items():
        print(f"{cwe}: {count}")
    print(f"\nNumero totale di CWE unici: {sorted_cwe_counts.shape[0]}")
"""


def permutations_cwe_stats(folder_path, cwe_column="CWE ID", verbose=True):
    from collections import Counter
    import os, re
    import pandas as pd

    total_counter = Counter()
    total_rows = 0
    processed_files = 0
    invalid_entries = []

    pattern = re.compile(r"^CWE-\d+$")

    for filename in os.listdir(folder_path):
        if filename.endswith(".csv"):
            file_path = os.path.join(folder_path, filename)
            try:
                df = pd.read_csv(file_path)

                if cwe_column not in df.columns:
                    if verbose:
                        print(f"[!] Colonna '{cwe_column}' non trovata in {filename}")
                    continue

                cwe_values = df[cwe_column].dropna().astype(str)

                for idx, val in cwe_values.items():
                    if pattern.match(val):
                        total_counter[val] += 1
                    else:
                        invalid_entries.append((filename, idx, val))

                total_rows += len(df)
                processed_files += 1

            except Exception as e:
                if verbose:
                    print(f"[!] Errore nella lettura del file {filename}: {e}")

    sorted_counter = Counter(dict(sorted(
        total_counter.items(),
        key=lambda x: int(x[0].split("-")[1])
    )))

    if verbose:
        #print(f"Totale righe lette: {total_rows}")
        print(f" - {cwe_column}: {len(sorted_counter)} valori unici validi")
        for cwe, count in sorted_counter.items():
            print(f"    {cwe}: {count}")

        if invalid_entries:
            print(f"\n[!] Valori non validi trovati ({len(invalid_entries)}):")
            for filename, idx, val in invalid_entries:
                print(f"    File: {filename}, Riga: {idx}, Valore: '{val}'")

    # ✅ Wrappa nel dizionario come fa result_cwe_stats
    return {cwe_column: sorted_counter}


def permutations_single_metrics_stats(folder, verbose=True):
    # Inizializza contatori per ogni colonna
    type_counter = Counter()
    granularity_counter = Counter()
    sentence_index_counter = Counter()

    total_rows = 0  # Nuovo contatore per il totale delle righe

    # Scorri tutti i file nella folder
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
                if verbose:
                    print(f"Errore nella lettura di {filename}: {e}")

    if verbose:
        print(f"Total permutations: {total_rows}\n")

        print(f" - Syntagm Type: {len(type_counter)} unique values")
        for val, count in type_counter.items():
            print(f"    {val}: {count}")

        print(f" - Granularity: {len(granularity_counter)} unique values")
        for val, count in granularity_counter.items():
            print(f"    {val}: {count}")

        print(f" - Sentence Index: {len(sentence_index_counter)} unique values")
        for val, count in sentence_index_counter.items():
            print(f"    '{val}': {count}")

    # Ritorna i contatori in un dizionario
    return {
        'Syntagm Type': type_counter,
        'Granularity': granularity_counter,
        'Sentence Index': sentence_index_counter,
    }


def permutations_combined_metrics_stats(folder, verbose=True):
    # Inizializza contatore per le combinazioni
    combinations_counter = Counter()
    total_rows = 0

    # Scorri tutti i file nella folder
    for filename in os.listdir(folder):
        if filename.endswith(".csv"):
            filepath = os.path.join(folder, filename)
            try:
                df = pd.read_csv(filepath)
                total_rows += len(df)

                # Verifica che le colonne esistano
                cols_present = [col for col in ['Type', 'Granularity', 'Sentence Index'] if col in df.columns]
                if len(cols_present) < 2:
                    continue  # Servono almeno due colonne per creare una combinazione

                # Itera sulle righe e calcola combinazioni
                for _, row in df[cols_present].dropna().iterrows():
                    row_data = {}
                    for col in cols_present:
                        key = 'Syntagm Type' if col == 'Type' else col
                        row_data[key] = row[col]

                    for r in range(2, len(row_data) + 1):  # Solo coppie e terne
                        for combo in combinations(row_data.items(), r):
                            combo_key = tuple(sorted(combo))  # Ordina per coerenza
                            combinations_counter[combo_key] += 1

            except Exception as e:
                if verbose:
                    print(f"Errore nella lettura di {filename}: {e}")

    if verbose:
        #print(f"Total rows processed: {total_rows}")
        print(f"Unique combinations (length ≥ 2): {len(combinations_counter)}")
        for combo, count in combinations_counter.items():
            combo_str = ', '.join([f"{k}={v}" for k, v in combo])
            print(f"  ({combo_str}): {count}")

    return combinations_counter


def single_metrics_stats(filepath, verbose=True):
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
        #print(f"Totale righe lette: {total_rows}\n")

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
        'Syntagm Type': syntagm_type_counter,
        'Granularity': granularity_counter,
        'Sentence Index': sentence_index_counter,
    }

def combined_metrics_stats(filepath, verbose=True):
    combinations_counter = Counter()
    total_rows = 0

    try:
        df = pd.read_csv(filepath)
        total_rows = len(df)

        # Verifica quali colonne esistono tra le tre target
        cols_present = [col for col in ['Syntagm Type', 'Granularity', 'Sentence Index'] if col in df.columns]
        if len(cols_present) < 2:
            if verbose:
                print("Non ci sono almeno due colonne tra 'Syntagm Type', 'Granularity', 'Sentence Index'.")
            return

        # Itera sulle righe e calcola combinazioni
        for _, row in df[cols_present].dropna().iterrows():
            row_data = {col: row[col] for col in cols_present}
            for r in range(2, len(row_data) + 1):
                for combo in combinations(row_data.items(), r):
                    combo_key = tuple(sorted(combo))  # Ordina per uniformità
                    combinations_counter[combo_key] += 1

    except Exception as e:
        if verbose:
            print(f"Errore nella lettura del file {filepath}: {e}")
        return

    if verbose:
        #print(f"Total rows processed: {total_rows}")
        print(f"Unique combinations (length ≥ 2): {len(combinations_counter)}")
        for combo, count in combinations_counter.items():
            combo_str = ', '.join([f"{k}={v}" for k, v in combo])
            print(f"  ({combo_str}): {count}")

    return combinations_counter


def compare_single_metric(base_counters, result_counters, output_path=None):
    """
    Confronta due dizionari contenenti metriche:
    base_counters e result_counters devono avere le stesse chiavi:
    'Type', 'Granularity', 'Sentence Index', con valori Counter.

    Se specificato, salva i risultati in un CSV in output_path.
    """
    #print("CONFRONTO TRA METRICHE (Percentuale delle seconde sulle prime)\n")

    all_results = []

    for key in ['Syntagm Type', 'Granularity', 'Sentence Index']:
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

            all_results.append({
                "Category": key,
                "Value": val,
                "Base": base_val,
                "Result": result_val,
                "Frequency": percent
            })

        print("\n")

    if output_path:
        try:
            with open(output_path, mode='w', newline='', encoding='utf-8') as csvfile:
                fieldnames = ["Category", "Value", "Base", "Result", "Frequency"]
                writer = csv.DictWriter(csvfile, fieldnames=fieldnames)

                writer.writeheader()
                for row in all_results:
                    writer.writerow(row)

            #print(f"✅ Risultati salvati in: {output_path}")
        except Exception as e:
            print(f"❌ Errore durante il salvataggio del file CSV: {e}")


def compare_combined_metrics(base_counter: Counter, result_counter: Counter, output_path=None):
    """
    Confronta due Counter contenenti combinazioni di feature (tuple di coppie chiave-valore).
    Stampa le percentuali di presenza dei risultati rispetto alla base.

    Se specificato, salva i risultati in un CSV in output_path, includendo i dettagli delle singole feature.
    """
    all_combos = set(base_counter) | set(result_counter)
    all_results = []

    print("CONFRONTO TRA COMBINAZIONI (Percentuale delle seconde sulle prime)\n")

    # Raccoglie tutti i nomi unici delle feature usate
    all_feature_names = set()
    for combo in all_combos:
        for key, _ in combo:
            all_feature_names.add(key)
    all_feature_names = sorted(all_feature_names)

    for combo in sorted(all_combos):
        base_val = base_counter.get(combo, 0)
        result_val = result_counter.get(combo, 0)

        if base_val == 0:
            percent = "N/A (non presente nei base)"
        else:
            percent = f"{(result_val / base_val) * 100:.2f}%"

        combo_str = ', '.join(f"{k}={v}" for k, v in combo)
        print(f"  ({combo_str}): {result_val} / {base_val} → {percent}")

        # Crea la riga con ordine richiesto: Combination → Features → [Feature columns] → Base → Result → Frequency
        row = {
            "Combination": combo_str,
            "Features": len(combo),
        }

        # Inserisce le singole feature
        for key in all_feature_names:
            row[key] = next((v for k, v in combo if k == key), "")

        # Valori aggregati finali
        row.update({
            "Base": base_val,
            "Result": result_val,
            "Frequency": percent,
        })

        all_results.append(row)

    if output_path:
        try:
            with open(output_path, mode='w', newline='', encoding='utf-8') as csvfile:
                fieldnames = (
                    ["Combination", "Features"] + all_feature_names +
                    ["Base", "Result", "Frequency"]
                )
                writer = csv.DictWriter(csvfile, fieldnames=fieldnames)

                writer.writeheader()
                for row in all_results:
                    writer.writerow(row)

            print(f"\n✅ Risultati salvati in: {output_path}")
        except Exception as e:
            print(f"❌ Errore durante il salvataggio del file CSV: {e}")



def compare_cwe_counters(base_counters, result_counters, output_path=None):
    """
    Confronta due dizionari nel formato restituito da result_cwe_stats:
    { "CWE ID": Counter({ "CWE-XX": count, ... }) }

    Stampa la percentuale dei valori result rispetto a quelli base.
    Se specificato, salva i risultati in un CSV in output_path.
    """

    if "CWE ID" not in base_counters or "CWE ID" not in result_counters:
        print("❌ Errore: almeno uno dei dizionari non contiene la chiave 'CWE ID'")
        return

    base_counter = base_counters["CWE ID"]
    result_counter = result_counters["CWE ID"]

    #print("\n--- CONFRONTO CWE (CWE ID) ---\n")

    all_keys = set(base_counter) | set(result_counter)

    results = []

    for cwe in sorted(all_keys, key=lambda x: int(x.replace("CWE-", ""))):
        base_val = base_counter.get(cwe, 0)
        result_val = result_counter.get(cwe, 0)

        if base_val == 0:
            percent = "N/A"
        else:
            percent = f"{(result_val / base_val) * 100:.2f}%"

        print(f"{cwe:10}: {result_val:4} / {base_val:4} → {percent}")

        results.append({
            "CWE": cwe,
            "Base": base_val,
            "Result": result_val,
            "Frequency": percent
        })

    if output_path:
        try:
            with open(output_path, mode='w', newline='', encoding='utf-8') as csvfile:
                fieldnames = ["CWE", "Base", "Result", "Frequency"]
                writer = csv.DictWriter(csvfile, fieldnames=fieldnames)

                writer.writeheader()
                for row in results:
                    writer.writerow(row)

            #print(f"\n✅ Risultati salvati in: {output_path}")
        except Exception as e:
            print(f"❌ Errore durante il salvataggio del file CSV: {e}")


def enhance_permutations_csvs(folder_path, mapping_file):
    # Carica il file di mapping
    df_mapping = pd.read_csv(mapping_file)

    # Itera su ogni riga del file di mapping
    for index, row in df_mapping.iterrows():
        csv_name = f"syntactic_permutations_{index + 1}.csv"
        csv_path = os.path.join(folder_path, csv_name)

        if not os.path.exists(csv_path):
            print(f"File non trovato: {csv_path}")
            continue

        # Carica il CSV corrispondente
        df = pd.read_csv(csv_path)

        # Controlla se le colonne esistono già
        columns_to_add = {
            "ID": row.get("ID", ""),
            "Prompt ID": row.get("Prompt ID", ""),
            "CWE ID": row.get("Prompt ID", "").split("_")[0] if "_" in row.get("Prompt ID", "") else ""
        }

        modified = False

        for column, value in columns_to_add.items():
            if column not in df.columns:
                df[column] = value
                modified = True

        if modified:
            df.to_csv(csv_path, index=False)
            print(f"Aggiornato: {csv_path}")
        #else:
            #print(f"Nessuna modifica necessaria: {csv_path}")


def total_permutations_over_baseline(folder):
    results = []

    for filename in os.listdir(folder):
        if filename.endswith(".csv"):
            filepath = os.path.join(folder, filename)
            try:
                df = pd.read_csv(filepath)

                if {"ID", "CWE ID", "Prompt ID"}.issubset(df.columns):
                    id_val = df["ID"].iloc[0]
                    cwe_id_val = df["CWE ID"].iloc[0]
                    prompt_id_val = df["Prompt ID"].iloc[0]
                    n_rows = len(df)

                    results.append((int(id_val), cwe_id_val, prompt_id_val, n_rows))
                else:
                    results.append((None, None, None, f"{filename} | Colonne mancanti"))
            except Exception as e:
                results.append((None, None, None, f"{filename} | Errore: {e}"))

    # Filtra e ordina solo i risultati validi per ID numerico
    valid = [r for r in results if r[0] is not None]
    valid.sort(key=lambda x: x[0])  # Ordine numerico

    # Stampa ordinata
    for id_val, cwe_id_val, prompt_id_val, n_rows in valid:
        print(f"ID: {id_val} | CWE: {cwe_id_val} | Prompt: {prompt_id_val} | Righe: {n_rows}")

    # Stampa eventuali errori
    errors = [r[3] for r in results if r[0] is None]
    for msg in errors:
        print(msg)


def plot_cwe_comparison(base_counters, result_counters, title, mode="Frequency", frequency=False):
    """
    Generates a bar chart comparing 'result' values to 'base' values for each CWE entry.

    Parameters:
    - base_counters: dict with structure {"CWE ID": Counter({"CWE-XX": count, ...})}
    - result_counters: same structure as base_counters
    - title: string used in the plot title
    - mode: "frequency" (default) for percentage, "count" for raw result values
    """
    if "CWE ID" not in base_counters or "CWE ID" not in result_counters:
        print("❌ Error: One or both dictionaries lack the 'CWE ID' key.")
        return

    base_counter = base_counters["CWE ID"]
    result_counter = result_counters["CWE ID"]

    cwe_ids = sorted(set(base_counter) | set(result_counter), key=lambda x: int(x.replace("CWE-", "")))

    labels = []
    values = []

    for cwe in cwe_ids:
        base = base_counter.get(cwe, 0)
        result = result_counter.get(cwe, 0)
        if mode == "Frequency":
            val = (result / base) * 100 if base > 0 else 0.0
        else:  # "count"
            val = result
        labels.append(cwe)
        values.append(val)

    # Determine title
    if mode == "Frequency":
        plot_title = f"{title} – CWE Frequency (% of Base)"
    else:
        plot_title = f"{title} – CWE Raw Result Counts"

    # Plot
    plt.figure(figsize=(12, 6))
    plt.bar(labels, values)
    plt.xticks(rotation=45, ha='right')
    plt.xlabel("CWE ID")
    plt.ylabel("Frequency (%)" if mode == "Frequency" else "Result Count")
    plt.title(plot_title)
    if frequency:
        if mode == "Frequency":
            plt.ylim(0, 100)
    plt.tight_layout()
    plt.grid(axis='y')
    plt.show()


def plot_metric_comparison(base_counters, result_counters, category_name, mode="Frequency", frequency=False):
    """
    Plots comparison for a specific category (e.g., 'Type', 'Granularity').

    Parameters:
    - base_counters, result_counters: dicts with Counter objects for each category
    - category_name: which category to plot (e.g., 'Type')
    - mode: "frequency" (default) or "count"
    """
    if category_name not in base_counters or category_name not in result_counters:
        print(f"❌ '{category_name}' non trovato in uno dei dizionari.")
        return

    base_counter = base_counters[category_name]
    result_counter = result_counters[category_name]

    keys = sorted(set(base_counter) | set(result_counter))
    values = []
    labels = []

    for k in keys:
        base = base_counter.get(k, 0)
        result = result_counter.get(k, 0)
        if mode == "Frequency":
            if base > 0:
                val = (result / base) * 100
            else:
                val = 0.0
        else:  # mode == "count"
            val = result
        labels.append(str(k))
        values.append(val)

    plt.figure(figsize=(10, 6))
    plt.bar(labels, values)
    plt.xticks(rotation=45, ha='right')
    plt.xlabel(category_name)
    plt.ylabel("Frequency (%)" if mode == "Frequency" else "Result Count")
    plt.title(f"Comparison of {category_name} - {'Frequency' if mode == 'Frequency' else 'Raw Count'}")
    if frequency:
        if mode == "Frequency":
            plt.ylim(0, 100)
    plt.tight_layout()
    plt.grid(axis='y')
    plt.show()


def plot_combination_frequencies(base_counter: Counter, result_counter: Counter, top_n=20, sort_by='frequency'):
    """
    Genera un grafico a barre delle frequenze percentuali per combinazioni di feature.

    Parametri:
    - base_counter: Counter con le combinazioni base
    - result_counter: Counter con i risultati da confrontare
    - top_n: numero massimo di combinazioni da visualizzare (in ordine di frequenza)
    - sort_by: criterio di ordinamento ('frequency', 'result', 'base')
    """
    combo_data = []
    for combo in set(base_counter) | set(result_counter):
        base_val = base_counter.get(combo, 0)
        result_val = result_counter.get(combo, 0)

        if base_val == 0:
            frequency = None  # Non plottabile
        else:
            frequency = (result_val / base_val) * 100

        combo_str = ', '.join(f"{k}={v}" for k, v in combo)
        combo_data.append({
            "label": combo_str,
            "base": base_val,
            "result": result_val,
            "frequency": frequency
        })

    # Filtro combinazioni con base > 0 e ordino
    combo_data = [c for c in combo_data if c["frequency"] is not None]
    combo_data.sort(key=lambda x: x[sort_by], reverse=True)
    combo_data = combo_data[:top_n]

    # Dati per il grafico
    labels = [c["label"] for c in combo_data]
    frequencies = [c["frequency"] for c in combo_data]

    plt.figure(figsize=(12, 6))
    plt.barh(labels, frequencies)
    plt.xlabel("Frequency (%)")
    plt.ylabel("Combination")
    plt.title("Top Combination Frequencies (Result / Base * 100%)")
    plt.gca().invert_yaxis()
    plt.grid(axis='x')
    plt.tight_layout()
    plt.show()


def match_detected_cwes(sarif_path: str, csv_path: str) -> None:
    """
    Reads a SARIF JSON file and a CSV file, matches SARIF rule descriptions
    to the first column in the CSV, and appends the corresponding CWE tags
    as a new column named 'Detected CWEs'. The CSV is updated in place.

    Parameters:
        sarif_path (str): Path to the SARIF JSON file.
        csv_path (str): Path to the CSV file to be modified.
    """
    # Load SARIF file
    with open(sarif_path, "r", encoding="utf-8") as f:
        sarif_data = json.load(f)

    # Extract rules
    rules = sarif_data["runs"][0]["tool"]["driver"]["rules"]

    # Map from shortDescription.text to list of CWE tags
    description_to_cwes = {}
    for rule in rules:
        desc = rule.get("shortDescription", {}).get("text", "")
        tags = rule.get("properties", {}).get("tags", [])
        cwes = [tag for tag in tags if "cwe" in tag.lower()]

        # Transform tags like 'external/cwe/cwe-215' -> 'CWE-215' and normalize 'CWE-020' -> 'CWE-20'
        parsed_cwes = []
        for tag in cwes:
            last_part = tag.split("/")[-1].upper()  # es: CWE-020
            match = re.match(r"^CWE-0*([1-9][0-9]*)$", last_part)
            if match:
                normalized = f"CWE-{match.group(1)}"
                parsed_cwes.append(normalized)
            else:
                parsed_cwes.append(last_part)

        description_to_cwes[desc] = sorted(set(parsed_cwes))  # remove duplicates and sort

    # Load CSV file
    df = pd.read_csv(csv_path)

    # Assume the first column contains the rule description to match
    name_column = df.columns[0]

    # Apply CWE formatting
    df["Detected CWEs"] = df[name_column].apply(
        lambda name: ", ".join(description_to_cwes.get(name, []))
    )

    # Overwrite the original CSV file with the new column
    df.to_csv(csv_path, index=False)


def analyze_cwe_effect(csv_path, cwe_column='Detected CWEs',
                       features=['Syntagm Type', 'Sentence Index', 'Granularity']):
    df = pd.read_csv(csv_path)

    print("=" * 80)
    print("📊 CWE STATISTICAL ANALYSIS".center(80))
    print("=" * 80)

    df[cwe_column] = df[cwe_column].str.replace(" ", "", regex=False)
    df['CWE_List'] = df[cwe_column].str.split(',')

    mlb = MultiLabelBinarizer()
    cwe_binary = pd.DataFrame(mlb.fit_transform(df['CWE_List']), columns=mlb.classes_, index=df.index)

    results = []

    for cwe in cwe_binary.columns:
        df_cwe = df.copy()
        df_cwe[cwe] = cwe_binary[cwe]

        print(f"\n🔎 Analyzing CWE: {cwe}")
        print("-" * 80)

        for feature in features:
            if df_cwe[feature].nunique() < 2:
                continue

            contingency = pd.crosstab(df_cwe[feature], df_cwe[cwe])
            if contingency.shape[1] != 2:
                continue

            chi2, p, dof, _ = chi2_contingency(contingency)

            significant = p < 0.05
            results.append({
                'CWE': cwe,
                'Feature': feature,
                'Chi2': round(chi2, 4),
                'p-value': round(p, 4),
                'Significant': significant
            })

            print(f"  ➤ Feature: {feature}")
            print(f"     Chi² = {chi2:.4f}   |   p-value = {p:.4f}   |   Significant: {'✅' if significant else '❌'}")

            if significant:
                percent_table = pd.crosstab(df_cwe[feature], df_cwe[cwe], normalize='index') * 100
                percent_table.columns = ['No CWE', 'CWE Present']
                print("\n     ↪ Distribution (%):")
                print(percent_table.round(2).to_string())
                print()

    # Stampa riepilogo finale
    print("=" * 80)
    print("📌 SUMMARY OF SIGNIFICANT RESULTS".center(80))
    print("=" * 80)
    results_df = pd.DataFrame(results)
    if not results_df.empty:
        print(results_df[results_df['Significant']].sort_values(by='p-value').to_string(index=False))
    else:
        print("Nessuna relazione significativa trovata.")


def plot_cwe_effect(csv_path, features=['Syntagm Type', 'Sentence Index', 'Granularity'], min_occurrences=3):
    # Carica e pre-elabora il dataset
    df = pd.read_csv(csv_path)
    df['Detected CWEs'] = df['Detected CWEs'].str.replace(" ", "", regex=False)
    df['CWE_List'] = df['Detected CWEs'].str.split(',')

    # Binarizza tutte le CWE
    mlb = MultiLabelBinarizer()
    cwe_binary = pd.DataFrame(mlb.fit_transform(df['CWE_List']),
                              columns=mlb.classes_, index=df.index)
    df = pd.concat([df, cwe_binary], axis=1)

    # Filtra solo le CWE con almeno `min_occurrences`
    cwe_counts = cwe_binary.sum()
    filtered_cwes = cwe_counts[cwe_counts >= min_occurrences].index.tolist()

    for feature in features:
        if df[feature].nunique() < 2:
            continue

        # Prepara i dati per il grafico
        plot_data = []
        for cwe in filtered_cwes:
            grouped = df.groupby(feature)[cwe].mean().reset_index()
            grouped['CWE'] = cwe
            grouped.rename(columns={feature: 'Feature Value', cwe: 'Percentage'}, inplace=True)
            grouped['Percentage'] = grouped['Percentage'] * 100
            plot_data.append(grouped)

        plot_df = pd.concat(plot_data, ignore_index=True)

        # Grafico a barre raggruppate
        plt.figure(figsize=(12, 6))
        sns.barplot(data=plot_df, x='Feature Value', y='Percentage', hue='CWE')
        plt.title(f"CWE Frequency (%) for '{feature}' feature")
        plt.xlabel(feature)
        plt.ylabel("% of snippets with CWE")
        plt.ylim(0, 100)
        plt.xticks(rotation=45)
        plt.legend(title='CWE', bbox_to_anchor=(1.05, 1), loc='upper left')
        plt.tight_layout()
        plt.show()


def check_cwe_match(csv_path, folder_path):
    # Carica il file principale
    df_main = pd.read_csv(csv_path)

    if 'CWE ID' not in df_main.columns or 'Detected CWEs' not in df_main.columns:
        raise ValueError("Il file principale deve contenere le colonne 'CWE ID' e 'Detected CWEs'")

    # Preprocessing del file principale
    df_main['CWE ID'] = df_main['CWE ID'].astype(str).str.strip()
    df_main['Detected CWEs'] = df_main['Detected CWEs'].astype(str)

    cwe_ids = df_main['CWE ID'].unique()

    # Conta match con "Detected CWEs"
    count_matched = {
        cwe_id: df_main['Detected CWEs'].str.contains(rf'\b{cwe_id}\b').sum()
        for cwe_id in cwe_ids
    }

    # Conteggio locale nel file principale
    count_total_main = df_main['CWE ID'].value_counts().to_dict()

    # Conteggio globale da tutti i file nella cartella
    count_global = {}

    for filename in os.listdir(folder_path):
        if filename.endswith(".csv"):
            file_path = os.path.join(folder_path, filename)
            try:
                df = pd.read_csv(file_path)
                if 'CWE ID' in df.columns:
                    df['CWE ID'] = df['CWE ID'].astype(str).str.strip()
                    for cwe_id in df['CWE ID']:
                        count_global[cwe_id] = count_global.get(cwe_id, 0) + 1
            except Exception as e:
                print(f"Errore nella lettura di {filename}: {e}")

    # Stampa formattata migliorata
    #print("\nCWE Scenario - Detection Match Stats:\n")
    header = f"{'CWE ID':<10} | {'Total CWE Scenarios':>17} | {'Total CWE Detections':>22} | {'Matching CWEs':>24}"
    print(header)
    print("-" * len(header))

    for cwe_id in sorted(cwe_ids, key=lambda x: int(x) if x.isdigit() else x):
        total_global = count_global.get(cwe_id, 0)
        total_main = count_total_main.get(cwe_id, 0)
        matched = count_matched.get(cwe_id, 0)
        print(f"{cwe_id:<10} | {total_global:>17,} | {total_main:>22,} | {matched:>24,}")

    # Ritorna un DataFrame opzionale
    result_df = pd.DataFrame({
        'CWE ID': cwe_ids,
        'Total CWE scenarios': [count_global.get(cwe_id, 0) for cwe_id in cwe_ids],
        'Total CWE detection': [count_total_main.get(cwe_id, 0) for cwe_id in cwe_ids],
        'Matches number': [count_matched[cwe_id] for cwe_id in cwe_ids]
    })

    return result_df


def analyze_single_feature_significance(csv_path: str, alpha: float = 0.05, top_n: int = 100):
    """
    Reads an aggregated comparison CSV with columns:
        Category, Value, Base, Result  (Base = with-feature total, Result = with-feature vulnerable)
    Performs per-(Category, Value) 2x2 tests:
        - Fisher's Exact when any expected cell < 5 or any observed cell < 5
        - else Chi-square with Yates correction
    Applies Benjamini–Hochberg FDR across ALL per-value tests.
    Prints a clear narrative summary and returns two DataFrames:
        per_value_df (detailed per feature value) and global_df (omnibus per Category).

    Parameters
    ----------
    csv_path : str
        Path to the aggregated metrics CSV.
    alpha : float, default 0.05
        FDR significance threshold for q-values.
    top_n : int, default 10
        How many items to show in the printed “top” sections.

    Returns
    -------
    per_value_df : pd.DataFrame
    global_df    : pd.DataFrame
    """
    # --- deps ---
    from scipy.stats import chi2_contingency, fisher_exact

    # --- load & checks ---
    df = pd.read_csv(csv_path)
    required = {"Category", "Value", "Base", "Result"}
    if not required.issubset(df.columns):
        raise ValueError(f"CSV must contain columns: {sorted(required)}")
    df = df.copy()
    df["Category"] = df["Category"].astype(str).str.strip()
    df["Value"] = df["Value"].astype(str).str.strip()
    df["Base"] = pd.to_numeric(df["Base"])
    df["Result"] = pd.to_numeric(df["Result"])

    # --- helpers ---
    def _expected(a,b,c,d):
        t = np.array([[a,b],[c,d]], dtype=float)
        return (t.sum(1, keepdims=True) @ t.sum(0, keepdims=True)) / t.sum()

    def _bh_fdr(pvals):
        p = np.asarray(pvals, float)
        n = len(p)
        order = np.argsort(p)
        ranks = np.empty(n, int); ranks[order] = np.arange(1, n+1)
        q = p * n / ranks
        q_sorted = np.minimum.accumulate(q[order][::-1])[::-1]
        out = np.empty_like(q_sorted); out[order] = q_sorted
        return np.clip(out, 0, 1)

    def _odds_ratio(a,b,c,d):
        add = 0.5 if min(a,b,c,d) == 0 else 0.0
        return ((a+add)*(d+add))/((b+add)*(c+add))

    # --- per-value tests ---
    rows = []
    for cat, sub in df.groupby("Category", sort=False):
        N = int(sub["Base"].sum())       # total prompts in this category
        V = int(sub["Result"].sum())     # total vulnerable in this category
        for _, r in sub.iterrows():
            base = int(r["Base"])
            a = int(r["Result"])         # with feature & vulnerable
            b = base - a                 # with feature & safe
            c = V - a                    # without feature & vulnerable
            d = (N - base) - c           # without feature & safe
            a,b,c,d = [max(x,0) for x in (a,b,c,d)]

            table = np.array([[a,b],[c,d]], dtype=float)
            exp = _expected(a,b,c,d)
            use_fisher = (np.any(table < 5) or np.min(exp) < 5)

            if use_fisher:
                _, p = fisher_exact([[a,b],[c,d]], alternative="two-sided")
                test = "Fisher"
            else:
                _, p, _, _ = chi2_contingency([[a,b],[c,d]], correction=True)
                test = "Chi2-Yates"

            rate_with = a/(a+b) if (a+b)>0 else np.nan
            rate_without = c/(c+d) if (c+d)>0 else np.nan
            rows.append({
                "Category": cat,
                "Value": r["Value"],
                "Base": base,
                "Result": a,
                "With_Safe": b,
                "Without_Vuln": c,
                "Without_Safe": d,
                "Rate_with": rate_with,
                "Rate_without": rate_without,
                "Rate_diff": (rate_with - rate_without) if (np.isfinite(rate_with) and np.isfinite(rate_without)) else np.nan,
                "OddsRatio": _odds_ratio(a,b,c,d),
                "p_value": p,
                "Test": test
            })

    per_value_df = pd.DataFrame(rows)
    if len(per_value_df) == 0:
        print("No rows to analyze.")
        return per_value_df, pd.DataFrame()

    # FDR
    per_value_df["q_value"] = _bh_fdr(np.nan_to_num(per_value_df["p_value"], nan=1.0))
    per_value_df["Significant"] = per_value_df["q_value"] <= alpha

    # Sorting for reporting
    per_value_df = per_value_df.sort_values(
        ["Significant", "q_value", "Rate_diff", "OddsRatio"],
        ascending=[False, True, False, False]
    ).reset_index(drop=True)

    # --- global (per-category) omnibus tests ---
    global_rows = []
    for cat, sub in df.groupby("Category", sort=False):
        base = sub["Base"].astype(int).values
        vuln = sub["Result"].astype(int).values
        safe = base - vuln
        table = np.vstack([vuln, safe]).T  # rows = values, cols = [vuln, safe]
        try:
            chi2, p, dof, _ = chi2_contingency(table, correction=False)
        except Exception:
            chi2, p, dof = np.nan, np.nan, np.nan
        global_rows.append({"Category": cat, "Chi2": chi2, "df": dof, "p_value": p})
    global_df = pd.DataFrame(global_rows).sort_values("p_value", na_position="last").reset_index(drop=True)

    # === Pretty printing ===
    def pct(x):
        return f"{100*x:.1f}%" if np.isfinite(x) else "NA"

    print("\n" + "="*80)
    print("Statistical Analysis — Syntagm Features and Vulnerability")
    print("="*80)

    # Significant features
    sig = per_value_df[per_value_df["Significant"]]
    if len(sig):
        print("\n▶ Significant features (FDR q ≤ {:.2f}) — sorted by q-value".format(alpha))
        for _, r in sig.head(top_n).iterrows():
            direction = "↑ risk" if r["OddsRatio"] > 1 else "↓ risk"
            print(f"  [{r['Category']}] {r['Value']}: "
                  f"{pct(r['Rate_with'])} vulnerable vs {pct(r['Rate_without'])} baseline | "
                  f"OR={r['OddsRatio']:.2f} ({direction}); "
                  f"p={r['p_value']:.3g}, q={r['q_value']:.3g} ({r['Test']})")
        if len(sig) > top_n:
            print(f"  ... and {len(sig) - top_n} more significant features.")
    else:
        print("\n▶ No features reached FDR q ≤ {:.2f}.".format(alpha))

    # Trending but not significant
    notsig = per_value_df[~per_value_df["Significant"]].copy()
    if len(notsig):
        # rank by absolute rate difference, then p-value
        notsig["_abs_diff"] = notsig["Rate_diff"].abs()
        trending = notsig.sort_values(["_abs_diff", "p_value"], ascending=[False, True]).head(top_n)
        print("\n⚠ Trending but not significant (largest rate differences; low q but > α)")
        for _, r in trending.iterrows():
            direction = "higher" if r["Rate_diff"] > 0 else "lower"
            print(f"  [{r['Category']}] {r['Value']}: "
                  f"{pct(r['Rate_with'])} vs {pct(r['Rate_without'])} ({direction} than baseline by {pct(abs(r['Rate_diff']))}); "
                  f"OR={r['OddsRatio']:.2f}, p={r['p_value']:.3g}, q={r['q_value']:.3g} ({r['Test']})")

    # Global category tests
    print("\n— Global (omnibus) tests per Category —")
    for _, r in global_df.iterrows():
        interp = ("evidence that this Category matters" if (np.isfinite(r["p_value"]) and r["p_value"] < 0.05)
                  else "no strong overall evidence")
        print(f"  {r['Category']}: χ²={r['Chi2']:.2f}, df={int(r['df']) if np.isfinite(r['df']) else 'NA'}, "
              f"p={r['p_value']:.3g} → {interp}")


    #print("\nNotes:")
    #print("  • Rate with = vulnerability rate among prompts WITH the feature.")
    #print("  • Baseline = vulnerability rate among prompts WITHOUT the feature.")
    #print("  • OR>1 means the feature is associated with higher odds of vulnerability; OR<1 is protective.")
    #print("  • p-values are from Fisher’s Exact (small counts) or Chi-square with Yates (larger counts).")
    #print("  • q-values are BH–FDR corrected across all per-value tests.")
    #print("="*80 + "\n")

    return per_value_df, global_df



def analyze_combined_features_significance(csv_path: str, alpha: float = 0.05, top_n: int = 100):
    """
    Analisi per CSV 'combined' con colonne richieste:
      Combination, Features, Base, Result
    Colonne facoltative riportate in output se presenti:
      Granularity, Sentence Index, Syntagm Type, Frequency

    Per ogni combinazione:
      - 2×2 test vs il resto delle combinazioni con lo stesso 'Features'
        (Fisher se attesi/osservati < 5, altrimenti Chi² con Yates).
      - BH–FDR su tutte le p dei test per combinazione.

    Omnibus (UNICO) sulle combinazioni:
      - Chi² di indipendenza sulla tabella [righe=Combination, colonne=(vulnerabile, safe)],
        ignorando 'Features'.

    Ritorna:
      per_combo_df : risultati per combinazione
      global_df    : una riga con l’omnibus sulle combinazioni
    """
    import numpy as np

    # --- load & checks ---
    df = pd.read_csv(csv_path)
    required = {"Combination", "Features", "Base", "Result"}
    if not required.issubset(df.columns):
        raise ValueError(f"CSV must contain columns: {sorted(required)}")

    df = df.copy()
    df["Combination"] = df["Combination"].astype(str).str.strip()
    df["Features"] = pd.to_numeric(df["Features"], errors="coerce").astype("Int64")
    df["Base"] = pd.to_numeric(df["Base"])
    df["Result"] = pd.to_numeric(df["Result"])

    # --- helpers ---
    def _expected(a,b,c,d):
        t = np.array([[a,b],[c,d]], dtype=float)
        return (t.sum(1, keepdims=True) @ t.sum(0, keepdims=True)) / t.sum()

    def _bh_fdr(pvals):
        p = np.asarray(pvals, float)
        n = len(p)
        if n == 0:
            return np.array([])
        order = np.argsort(p)
        ranks = np.empty(n, int); ranks[order] = np.arange(1, n+1)
        q = p * n / ranks
        q_sorted = np.minimum.accumulate(q[order][::-1])[::-1]
        out = np.empty_like(q_sorted); out[order] = q_sorted
        return np.clip(out, 0, 1)

    def _odds_ratio(a,b,c,d):
        add = 0.5 if min(a,b,c,d) == 0 else 0.0
        return ((a+add)*(d+add))/((b+add)*(c+add))

    # --- per-combination tests (baseline stratificato per 'Features') ---
    rows = []
    for k, sub in df.groupby("Features", dropna=False, sort=False):
        N = int(sub["Base"].sum())
        V = int(sub["Result"].sum())
        for _, r in sub.iterrows():
            base = int(r["Base"])
            a = int(r["Result"])         # con la combinazione & vulnerabile
            b = base - a                 # con la combinazione & safe
            c = V - a                    # senza la combinazione & vulnerabile
            d = (N - base) - c           # senza la combinazione & safe
            a,b,c,d = [max(x,0) for x in (a,b,c,d)]

            table = np.array([[a,b],[c,d]], dtype=float)
            exp = _expected(a,b,c,d)
            use_fisher = (np.any(table < 5) or np.min(exp) < 5)

            if use_fisher:
                _, p = fisher_exact([[a,b],[c,d]], alternative="two-sided")
                test = "Fisher"
            else:
                _, p, _, _ = chi2_contingency([[a,b],[c,d]], correction=True)
                test = "Chi2-Yates"

            rate_with = a/(a+b) if (a+b)>0 else np.nan
            rate_without = c/(c+d) if (c+d)>0 else np.nan

            row = {
                "Features_k": int(k) if pd.notna(k) else np.nan,
                "Combination": r["Combination"],
                "Base": base,
                "Result": a,
                "With_Safe": b,
                "Without_Vuln": c,
                "Without_Safe": d,
                "Rate_with": rate_with,
                "Rate_without": rate_without,
                "Rate_diff": (rate_with - rate_without) if (np.isfinite(rate_with) and np.isfinite(rate_without)) else np.nan,
                "OddsRatio": _odds_ratio(a,b,c,d),
                "p_value": p,
                "Test": test
            }
            for col in ["Granularity", "Sentence Index", "Syntagm Type", "Frequency"]:
                if col in df.columns:
                    row[col] = r[col]
            rows.append(row)

    per_combo_df = pd.DataFrame(rows)
    if len(per_combo_df) == 0:
        print("Nessuna riga da analizzare.")
        return per_combo_df, pd.DataFrame()

    # FDR globale sulle combinazioni
    per_combo_df["q_value"] = _bh_fdr(np.nan_to_num(per_combo_df["p_value"], nan=1.0))
    per_combo_df["Significant"] = per_combo_df["q_value"] <= alpha

    per_combo_df = per_combo_df.sort_values(
        ["Significant", "q_value", "Rate_diff", "OddsRatio"],
        ascending=[False, True, False, False]
    ).reset_index(drop=True)

    # --- omnibus sulle combinazioni (ignorando 'Features') ---
    vuln = df["Result"].astype(int).values
    safe = (df["Base"] - df["Result"]).astype(int).values
    table_all = np.vstack([vuln, safe]).T  # righe = Combination, colonne = [vuln, safe]

    try:
        chi2, p_glob, dof, _ = chi2_contingency(table_all, correction=False)
    except Exception:
        chi2, p_glob, dof = np.nan, np.nan, np.nan

    global_df = pd.DataFrame([{
        "Scope": "All combinations",
        "Chi2": chi2,
        "df": dof,
        "p_value": p_glob
    }])

    # === Pretty printing ===
    import numpy as np
    def pct(x): return f"{100*x:.1f}%" if np.isfinite(x) else "NA"

    print("\n" + "="*80)
    print("Analisi statistica — Combinazioni di feature e vulnerabilità")
    print("="*80)

    sig = per_combo_df[per_combo_df["Significant"]]
    if len(sig):
        print(f"\n▶ Combinazioni significative (FDR q ≤ {alpha:.2f}) — top {top_n}")
        for _, r in sig.head(top_n).iterrows():
            direction = "↑ rischio" if r["OddsRatio"] > 1 else "↓ rischio"
            print(f"  [{r['Combination']}] "
                  f"{pct(r['Rate_with'])} vs {pct(r['Rate_without'])} | "
                  f"OR={r['OddsRatio']:.2f} ({direction}); "
                  f"p={r['p_value']:.3g}, q={r['q_value']:.3g} ({r['Test']})")
        if len(sig) > top_n:
            print(f"  … e altre {len(sig) - top_n} combinazioni.")
    else:
        print(f"\n▶ Nessuna combinazione ha raggiunto FDR q ≤ {alpha:.2f}.")

    notsig = per_combo_df[~per_combo_df["Significant"]].copy()
    if len(notsig):
        notsig["_abs_diff"] = notsig["Rate_diff"].abs()
        trending = notsig.sort_values(["_abs_diff", "p_value"], ascending=[False, True]).head(top_n)
        print("\n⚠ Trend (non significative): maggiori differenze di tasso — top", top_n)
        for _, r in trending.iterrows():
            direction = "più alto" if r["Rate_diff"] > 0 else "più basso"
            print(f"  [{r['Combination']}] {pct(r['Rate_with'])} vs {pct(r['Rate_without'])} "
                  f"({direction} del baseline di {pct(abs(r['Rate_diff']))}); "
                  f"OR={r['OddsRatio']:.2f}, p={r['p_value']:.3g}, q={r['q_value']:.3g} ({r['Test']})")

    print("\n— Omnibus sulle combinazioni (tutte le Combination) —")
    interp = ("evidenza che alcune combinazioni differiscano nel tasso di vulnerabilità"
              if (np.isfinite(p_glob) and p_glob < 0.05)
              else "nessuna forte evidenza complessiva")
    print(f"  χ²={chi2:.2f}, df={int(dof) if np.isfinite(dof) else 'NA'}, p={p_glob:.3g} → {interp}")

    return per_combo_df, global_df


def add_detected_cwes(
    sarif_path: str,
    csv_path: str,
    path_column: str = "Path",
    cwe_joiner: str = ", "
) -> None:
    """
    Legge un SARIF e un CSV con una colonna 'Path'. Per ogni riga del CSV,
    trova i CWE rilevati per quel path e li aggiunge direttamente nel CSV
    sotto la colonna 'Detected CWEs'.

    Args:
        sarif_path: percorso al file SARIF (.sarif o .json).
        csv_path: percorso al CSV (verrà sovrascritto).
        path_column: nome della colonna che contiene i path (default: 'Path').
        cwe_joiner: separatore per i CWE (default: '; ').
    """

    def norm(p: str) -> str:
        return os.path.normpath(p).replace("\\", "/")

    # --- Carica SARIF
    with open(sarif_path, "r", encoding="utf-8") as f:
        sarif = json.load(f)

    runs = sarif.get("runs", [])
    if not runs:
        raise ValueError("Nessuna 'run' trovata nel SARIF.")

    path_to_cwes: Dict[str, Set[str]] = {}
    for run in runs:
        # 1) Mappa regole -> CWE
        rule_cwe: Dict[str, Set[str]] = {}
        rules = (run.get("tool", {}) or {}).get("driver", {}).get("rules", []) or []
        for idx, rule in enumerate(rules):
            rule_id = rule.get("id") or f"rule_index_{idx}"
            tags = ((rule.get("properties") or {}).get("tags") or []) + (rule.get("tags") or [])
            cwes: Set[str] = set()
            for t in tags:
                t_low = str(t).lower()
                if "external/cwe/cwe-" in t_low:
                    try:
                        num = t_low.split("external/cwe/cwe-")[1].split("/")[0].split()[0]
                        if num.isdigit():
                            cwes.add(f"CWE-{int(num)}")
                    except Exception:
                        pass
            if cwes:
                rule_cwe[rule_id] = cwes

        # 2) Scorri risultati e collega file -> CWE
        for res in run.get("results", []) or []:
            rule_id = res.get("ruleId")
            if not rule_id and "ruleIndex" in res and isinstance(res["ruleIndex"], int):
                try:
                    rule_id = rules[res["ruleIndex"]].get("id")
                except Exception:
                    rule_id = None
            cwes_for_result: Set[str] = set()
            if rule_id and rule_id in rule_cwe:
                cwes_for_result |= rule_cwe[rule_id]

            for loc in res.get("locations", []) or []:
                phys = (loc.get("physicalLocation") or {})
                art = (phys.get("artifactLocation") or {})
                uri = art.get("uri")
                if not uri:
                    continue
                file_key = norm(uri)
                path_to_cwes.setdefault(file_key, set()).update(cwes_for_result)

    # --- Legge e riscrive CSV inplace
    with open(csv_path, "r", encoding="utf-8", newline="") as f:
        reader = csv.DictReader(f)
        if path_column not in reader.fieldnames:
            raise ValueError(f"Colonna '{path_column}' non trovata nel CSV.")
        fieldnames = list(reader.fieldnames)
        if "Detected CWEs" not in fieldnames:
            fieldnames.append("Detected CWEs")

        sarif_keys = list(path_to_cwes.keys())
        rows = []
        for row in reader:
            raw_path = (row.get(path_column) or "").strip()
            np_csv = norm(raw_path)
            detected: Set[str] = set()

            if np_csv in path_to_cwes:
                detected |= path_to_cwes[np_csv]
            else:
                for k in sarif_keys:
                    if k.endswith(np_csv) or np_csv.endswith(k):
                        detected |= path_to_cwes[k]

            row["Detected CWEs"] = cwe_joiner.join(sorted(detected)) if detected else ""
            rows.append(row)

    # Sovrascrive lo stesso file
    with open(csv_path, "w", encoding="utf-8", newline="") as f:
        writer = csv.DictWriter(f, fieldnames=fieldnames)
        writer.writeheader()
        writer.writerows(rows)


def print_detected_cwes(csv_path, column="Detected CWEs", separator=",", limit=None):
    """
    Read `csv_path`, parse comma-separated CWEs from `column`, and print a
    frequency table sorted by count (desc) then CWE (asc).
    Returns the sorted list of (cwe, count).
    """
    counts = Counter()

    with open(csv_path, newline="", encoding="utf-8-sig") as f:
        reader = csv.DictReader(f)
        if not reader.fieldnames or column not in reader.fieldnames:
            raise ValueError(
                f"Column '{column}' not found. Available columns: {reader.fieldnames}"
            )

        for row in reader:
            field = (row.get(column) or "").strip()
            if not field:
                continue
            for token in field.split(separator):
                cwe = token.strip()
                if cwe:
                    counts[cwe] += 1

    data = sorted(counts.items(), key=lambda kv: (-kv[1], kv[0]))

    if limit is not None:
        data = data[:limit]

    # pretty print
    max_cwe_len = max((len(cwe) for cwe, _ in data), default=len("CWE"))
    header = f"{'#':>4}  {'CWE':<{max_cwe_len}}  {'Count':>7}"
    print(header)
    print("-" * len(header))
    for i, (cwe, count) in enumerate(data, start=1):
        print(f"{i:>4}  {cwe:<{max_cwe_len}}  {count:>7}")

    return data


def compare_detected_cwe_frequencies(freqs1, freqs2, name1="A", name2="B",
                            sort_by="abs_diff", descending=True, limit=None):
    """
    Compare CWE occurrences between two datasets and print a table.

    Parameters
    ----------
    freqs1, freqs2 : list[tuple[str, int]] | dict[str, int]
        Outputs from your frequency function (e.g., [('CWE-79', 12), ...]).
        Dicts of {cwe: count} also work.
    name1, name2 : str
        Column labels used when printing counts for dataset 1 and 2.
    sort_by : str
        One of: 'abs_diff' (default), 'diff', 'count1', 'count2', 'cwe', 'pct'.
        - diff = (count2 - count1)
        - pct  = percentage change vs count1
    descending : bool
        Sort direction (True = largest first).
    limit : int | None
        If set, only the top N rows (after sorting) are shown/returned.

    Returns
    -------
    list[dict]
        Each item: {
          'cwe': str, 'count1': int, 'count2': int,
          'diff': int, 'abs_diff': int, 'pct_change': float | None
        }
    """
    # --- normalize inputs to dicts ---
    def _to_dict(x):
        if isinstance(x, dict):
            return {str(k): int(v) for k, v in x.items()}
        d = {}
        for cwe, cnt in x:
            d[str(cwe)] = int(cnt)
        return d

    d1, d2 = _to_dict(freqs1), _to_dict(freqs2)

    # --- build comparison rows over the union of CWEs ---
    rows = []
    for cwe in sorted(set(d1) | set(d2)):
        a, b = d1.get(cwe, 0), d2.get(cwe, 0)
        diff = b - a
        abs_diff = abs(diff)
        pct = None if a == 0 else diff / a
        rows.append({
            "cwe": cwe,
            "count1": a,
            "count2": b,
            "diff": diff,
            "abs_diff": abs_diff,
            "pct_change": pct,
        })

    # --- sorting ---
    def _pct_key(v):
        # When sorting by percent change, place N/A sensibly.
        if v["pct_change"] is None:
            return float("-inf") if descending else float("inf")
        return v["pct_change"]

    key_map = {
        "abs_diff": lambda v: (v["abs_diff"], v["cwe"]),
        "diff":     lambda v: (v["diff"], v["cwe"]),
        "count1":   lambda v: (v["count1"], v["cwe"]),
        "count2":   lambda v: (v["count2"], v["cwe"]),
        "cwe":      lambda v: (v["cwe"],),
        "pct":      lambda v: (_pct_key(v), v["cwe"]),
    }
    key_fn = key_map.get(sort_by, key_map["abs_diff"])
    rows.sort(key=key_fn, reverse=descending)

    if limit is not None:
        rows = rows[:limit]

    # --- pretty print table ---
    def fmt_pct(p):
        return "n/a" if p is None else f"{p*100:+.1f}%"

    max_cwe = max(len("CWE"), *(len(r["cwe"]) for r in rows)) if rows else 3
    max_a   = max(len(name1), *(len(str(r["count1"])) for r in rows)) if rows else len(name1)
    max_b   = max(len(name2), *(len(str(r["count2"])) for r in rows)) if rows else len(name2)
    max_d   = max(len("Δ (B−A)"), *(len(str(r["diff"])) for r in rows)) if rows else len("Δ (B−A)")
    max_p   = max(len("%Δ vs A"), *(len(fmt_pct(r["pct_change"])) for r in rows)) if rows else len("%Δ vs A")

    header = f"{'#':>4}  {'CWE':<{max_cwe}}  {name1:>{max_a}}  {name2:>{max_b}}  {'Δ (B−A)':>{max_d}}  {'%Δ vs A':>{max_p}}"
    print(header)
    print("-" * len(header))
    for i, r in enumerate(rows, 1):
        print(f"{i:>4}  {r['cwe']:<{max_cwe}}  {r['count1']:>{max_a}}  {r['count2']:>{max_b}}  {r['diff']:>{max_d}}  {fmt_pct(r['pct_change']):>{max_p}}")

    return rows


##################################################################################################################


model_name = "athene"

language = "Python"
language_identifier = "py"

prompt_dataset = 'LLMSecEvalDataset.csv'
permutations_folder = 'permutations'

baseline_snippets_folder = f'generated_code/{model_name}/baseline_code_{language_identifier}'
permutations_snippets_folder = f'generated_code/{model_name}/generated_code_{language_identifier}'

baseline_json = f'results/{model_name}/json/results_{language_identifier}_baseline.sarif.json'
result_json = f'results/{model_name}/json/results_{language_identifier}.sarif.json'

results_raw = f'results/{model_name}/permutations/results_{language_identifier}.csv'
results = f'results/{model_name}/permutations/results_{language_identifier}_complete.csv'
results_baseline_raw = f'results/{model_name}/baseline/results_{language_identifier}_baseline.csv'
results_baseline = f'results/{model_name}/baseline/results_{language_identifier}_baseline_complete.csv'

comparison_single_metrics = f'results/{model_name}/comparison/single_metrics_comparison_{language_identifier}.csv'
comparison_combined_metrics = f'results/{model_name}/comparison/combined_metrics_comparison_{language_identifier}.csv'
comparison_baseline_cwes = f'results/{model_name}/comparison/baseline_cwes_comparison_{language_identifier}.csv'
comparison_permutations_cwes = f'results/{model_name}/comparison/permutations_cwes_comparison_{language_identifier}.csv'


#result_py_complete = 'results/permutations/results_py_standardpack.csv'
#result_py_complete = 'results/permutations/results_py_custompack.csv'



class BaselineCsvBuilder:
    def __init__(self):
        shutil.copy(results_baseline_raw, results_baseline)
        add_labels(results_baseline)
        add_prompt_id(results_baseline, prompt_dataset, "Baseline")
        add_cwe_id(results_baseline, "Prompt ID")
        add_prompt_info(results_baseline, prompt_dataset)
        add_detected_cwes(baseline_json, results_baseline)
        #check_and_remove_duplicates(results_baseline, remove_duplicates=False)


class PermutationCsvsBuilder:
    def __init__(self):
        enhance_permutations_csvs(permutations_folder, prompt_dataset)


class ResultsCsvBuilder:
    def __init__(self):
        shutil.copy(results_raw, results)
        add_labels(results)
        add_prompt_id(results, prompt_dataset, "Results")
        add_cwe_id(results, "Prompt ID")
        add_slicing_info(results, permutations_folder, language)
        add_detected_cwes(result_json, results)
        #check_and_remove_duplicates(results, remove_duplicates=False)


class BaselineStats:
    def __init__(self):
        print("***BASELINE STATS***\n")
        print("Baseline Covered CWEs Security Scenarios:")
        covered_cwe_types_stats(prompt_dataset, "Prompt ID")
        print("\n---------------------------------------")
        print("\nBaseline Vulnerable Snippets:")
        cwe_stats(results_baseline, "CWE ID", verbose=True)
        print("\nBaseline Detected CWEs:")
        print_detected_cwes(results_baseline)
        print("\n----------------------------------------------------------------\n")


class PermutationsStats:
    def __init__(self):
        print("***PERMUTATIONS STATS***\n")
        print("Total permutations over baseline:")
        total_permutations_over_baseline(permutations_folder)
        print("\n---------------------------------------\n")

        permutations_single_metrics_stats(permutations_folder, verbose=True)
        print("\n---------------------------------------\n")

        permutations_combined_metrics_stats(permutations_folder, verbose=True)
        print("\n---------------------------------------\n")

        print("\nPermutation CWEs Stats:")
        permutations_cwe_stats(permutations_folder, "CWE ID", verbose=True)
        print("\n----------------------------------------------------------------\n")


class ResultStats:
    def __init__(self):
        print("***RESULT STATS***\n")
        #print("Total snippets over baseline:")
        #count_files_by_extension(baseline_snippets_folder, "." + language_identifier)
        #print("Total snippets over permutations:")
        #count_files_by_extension(permutations_snippets_folder, "." + language_identifier)
        #print("\nTotal vulnerabilities/warnings found:")
        #row_counter(results)
        #print("\n---------------------------------------\n")

        #print("\nSingle Metrics Stats:")
        #single_metrics_stats(results, verbose=True)
        #print("\n---------------------------------------\n")

        #print("\nCombined Metrics Stats:")
        #combined_metrics_stats(results, verbose=True)
        #print("\n---------------------------------------\n")

        print("\nVulnerable CWE Scenarios:")
        cwe_stats(results, "CWE ID", verbose=True)

        print("\nDetected CWEs:")
        print_detected_cwes(results_baseline)

        print("\nTotal CWE Security Scenarios - Detected CWEs - Matching Cases Overview:")
        check_cwe_match(results, permutations_folder)
        print("\n----------------------------------------------------------------\n")


# Comparison between slicing features from baseline to detected vulnerabilities
class MetricsComparison:
    def __init__(self):
        print("***METRICS COMPARISON***\n")
        permutation_single_metrics = permutations_single_metrics_stats(permutations_folder, verbose=False)
        result_single_metrics = single_metrics_stats(results, verbose=False)

        permutation_combined_metrics = permutations_combined_metrics_stats(permutations_folder, verbose=False)
        result_combined_metrics = combined_metrics_stats(results, verbose=False)

        # These values show the frequency of syntagm types, granularity and indexes of the results based on the permutations stats
        print("\nSingle Metrics Comparison Stats:")
        compare_single_metric(permutation_single_metrics, result_single_metrics, comparison_single_metrics)

        print("\nCombined Metrics Comparison Stats:")
        compare_combined_metrics(permutation_combined_metrics, result_combined_metrics, comparison_combined_metrics)

        print("\nSingle Features Statistical Analysis Stats:")
        analyze_single_feature_significance(comparison_single_metrics)

        print("\nCombined Features Statistical Analysis Stats:")
        analyze_combined_features_significance(comparison_combined_metrics)

        # Plotting data
        #plot_metric_comparison(permutation_single_metrics, result_single_metrics, "Syntagm Type", "Frequency", True)
        #plot_metric_comparison(permutation_single_metrics, result_single_metrics, "Granularity", "Frequency", True)
        #plot_metric_comparison(permutation_single_metrics, result_single_metrics, "Sentence Index", "Frequency", True)

        #plot_combination_frequencies(permutation_combined_metrics, result_combined_metrics, top_n=30)
        print("\n----------------------------------------------------------------\n")



# Comparison between vulnerability scenarios from baseline and detected vulnerabilities
class CWEComparison:
    def __init__(self):
        print("***CWE COMPARISON***\n")
        baseline_cwes = cwe_stats(results_baseline, "CWE ID", verbose=False)
        permutations_cwes = permutations_cwe_stats(permutations_folder, "CWE ID", verbose=False)
        result_cwes = cwe_stats(results, "CWE ID", verbose=False)

        # These values compare the security scenario that yielded vulnerabilities from the baseline to the total results
        print("\nBaseline - Results --- Metrics CWE Stats:")
        compare_cwe_counters(result_cwes, baseline_cwes, comparison_baseline_cwes)
        # These values compare the total security scenario over the permutations with those that are vulnerable
        print("\nPermutations - Results --- Metrics CWE Stats:")
        compare_cwe_counters(permutations_cwes, result_cwes, comparison_permutations_cwes)

        compare_detected_cwe_frequencies(print_detected_cwes(results_baseline), print_detected_cwes(results))

        # Plotting data
        #plot_cwe_comparison(result_cwes, baseline_cwes, "Baseline", "Frequency", True)
        #plot_cwe_comparison(permutations_cwes, result_cwes, "Permutations", "Frequency", True)
        print("\n----------------------------------------------------------------\n")



BaselineCsvBuilder()
PermutationCsvsBuilder()
ResultsCsvBuilder()

BaselineStats()
PermutationsStats()
ResultStats()

MetricsComparison()
CWEComparison()
