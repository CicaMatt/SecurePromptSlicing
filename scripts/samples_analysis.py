import csv
import json
import math
import os
import re
import shutil
import tempfile
import unicodedata
from collections import Counter
from decimal import Decimal, ROUND_HALF_UP
from itertools import combinations
from pathlib import Path
from typing import Dict, Set, List, Tuple, Literal, Union, Sequence, Optional, Any

import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
from scipy.sparse.linalg import _norm
from scipy.stats import chi2_contingency, fisher_exact, chi2
from sklearn.preprocessing import MultiLabelBinarizer
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


def single_metrics_stats(filepath, verbose=True, verify_consistency=True):
    """
    Read a CSV, collapse rows sharing the same 'Path' into one record,
    then count occurrences of 'Syntagm Type', 'Granularity', and 'Sentence Index'.

    Parameters
    ----------
    filepath : str
        Path to the CSV file.
    verbose : bool
        Whether to print a summary.
    verify_consistency : bool
        If True, checks that within each Path-group the fields of interest are identical.
        Prints a warning if inconsistencies are found (but still proceeds using the first row).
    """
    syntagm_type_counter = Counter()
    granularity_counter = Counter()
    sentence_index_counter = Counter()

    try:
        df = pd.read_csv(filepath)
    except Exception as e:
        if verbose:
            print(f"Errore nella lettura del file {filepath}: {e}")
        return {
            'Syntagm Type': syntagm_type_counter,
            'Granularity': granularity_counter,
            'Sentence Index': sentence_index_counter,
        }

    required_cols = ['Path', 'Syntagm Type', 'Granularity', 'Sentence Index']
    missing = [c for c in required_cols if c not in df.columns]
    if missing:
        if verbose:
            print(f"Colonne mancanti nel file: {', '.join(missing)}")
        # Proceed with whatever is available after deduping by Path (if present)

    # If 'Path' exists, collapse to one row per Path; else, we just work as-is
    if 'Path' in df.columns:
        # Optional consistency check
        if verify_consistency:
            cols_to_check = [c for c in ['Syntagm Type', 'Granularity', 'Sentence Index'] if c in df.columns]
            if cols_to_check:
                bad_paths = []
                for path_val, g in df.groupby('Path'):
                    for col in cols_to_check:
                        # Count distinct non-null values within the group
                        distinct_vals = g[col].dropna().unique()
                        if len(distinct_vals) > 1:
                            bad_paths.append((path_val, col, distinct_vals))
                if bad_paths and verbose:
                    print("ATTENZIONE: trovate incongruenze nei gruppi per 'Path' "
                          "(verranno comunque usati i primi valori del gruppo):")
                    for path_val, col, vals in bad_paths[:10]:
                        print(f"  - Path={path_val!r}, colonna '{col}' ha valori multipli: {list(vals)}")
                    if len(bad_paths) > 10 and verbose:
                        print(f"  ... e altri {len(bad_paths) - 10} gruppi con incongruenze.")

        # Collapse groups by taking the first row per Path (safe because values should match)
        df_merged = df.sort_index().groupby('Path', as_index=False).first()
    else:
        df_merged = df  # No Path column; nothing to merge

    # Now count on the merged dataframe
    if 'Syntagm Type' in df_merged.columns:
        syntagm_type_counter.update(df_merged['Syntagm Type'].dropna())
    if 'Granularity' in df_merged.columns:
        granularity_counter.update(df_merged['Granularity'].dropna())
    if 'Sentence Index' in df_merged.columns:
        sentence_index_counter.update(df_merged['Sentence Index'].dropna())

    if verbose:
        def _print_counter(title, c):
            print(f" - {title}: {len(c)} valori unici")
            for val, count in c.items():
                print(f"    {val!r}: {count}")

        _print_counter("Syntagm Type", syntagm_type_counter)
        _print_counter("Granularity", granularity_counter)
        _print_counter("Sentence Index", sentence_index_counter)

    return {
        'Syntagm Type': syntagm_type_counter,
        'Granularity': granularity_counter,
        'Sentence Index': sentence_index_counter,
    }

def combined_metrics_stats(filepath, verbose=True, verify_consistency=True):
    """
    Read a CSV, collapse rows sharing the same 'Path' into one record,
    then count combinations (size ≥ 2) among the present columns of:
    ['Syntagm Type', 'Granularity', 'Sentence Index'].

    Parameters
    ----------
    filepath : str
        Path to the CSV file.
    verbose : bool
        Whether to print a summary.
    verify_consistency : bool
        If True, checks that within each Path-group the fields of interest are identical.
        Prints a warning if inconsistencies are found (but still proceeds using the first row).
    """
    combinations_counter = Counter()

    try:
        df = pd.read_csv(filepath)
    except Exception as e:
        if verbose:
            print(f"Errore nella lettura del file {filepath}: {e}")
        return combinations_counter

    target_cols = ['Syntagm Type', 'Granularity', 'Sentence Index']
    cols_present = [c for c in target_cols if c in df.columns]
    if len(cols_present) < 2:
        if verbose:
            print("Non ci sono almeno due colonne tra 'Syntagm Type', 'Granularity', 'Sentence Index'.")
        return combinations_counter

    # If 'Path' exists, collapse to one row per Path; otherwise, work as-is
    if 'Path' in df.columns:
        if verify_consistency:
            bad_paths = []
            for path_val, g in df.groupby('Path'):
                for col in cols_present:
                    distinct_vals = g[col].dropna().unique()
                    if len(distinct_vals) > 1:
                        bad_paths.append((path_val, col, distinct_vals))
            if bad_paths and verbose:
                print("ATTENZIONE: trovate incongruenze nei gruppi per 'Path' "
                      "(verranno comunque usati i primi valori del gruppo):")
                for path_val, col, vals in bad_paths[:10]:
                    print(f"  - Path={path_val!r}, colonna '{col}' ha valori multipli: {list(vals)}")
                if len(bad_paths) > 10:
                    print(f"  ... e altri {len(bad_paths) - 10} gruppi con incongruenze.")
        # collapse groups by taking the first row per Path
        df_merged = df.sort_index().groupby('Path', as_index=False).first()
        total_units = len(df_merged)
    else:
        df_merged = df
        total_units = len(df_merged)

    # Work only with rows where all required-present columns are non-null
    work_df = df_merged[cols_present].dropna()

    # Build combination counts (size ≥ 2)
    for _, row in work_df.iterrows():
        row_data = {col: row[col] for col in cols_present}
        for r in range(2, len(row_data) + 1):
            for combo in combinations(row_data.items(), r):
                combo_key = tuple(sorted(combo))  # normalize order
                combinations_counter[combo_key] += 1

    if verbose:
        print(f"Unità considerate (dopo merge per Path se presente): {total_units}")
        print(f"Combinazioni uniche (lunghezza ≥ 2): {len(combinations_counter)}")
        for combo, count in combinations_counter.items():
            combo_str = ', '.join([f"{k}={v!r}" for k, v in combo])
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
    # Prova a caricare il file principale con gestione file vuoti
    try:
        df_main = pd.read_csv(csv_path)
    except pd.errors.EmptyDataError:
        # CSV completamente vuoto (nessuna colonna, nessuna riga)
        df_main = pd.DataFrame()

    # Se non ci sono colonne attese, ma il file non è completamente vuoto
    if not df_main.empty and ('CWE ID' not in df_main.columns or 'Detected CWEs' not in df_main.columns):
        raise ValueError("Il file principale deve contenere le colonne 'CWE ID' e 'Detected CWEs'")

    # Normalizza struttura minima quando df_main è vuoto o privo di colonne
    if df_main.empty:
        # assicura colonne per l'output coerente
        df_main = pd.DataFrame(columns=['CWE ID', 'Detected CWEs'])

    # Preprocessing del file principale
    df_main['CWE ID'] = df_main['CWE ID'].astype(str).str.strip()
    # Evita 'nan' letterale nei match
    df_main['Detected CWEs'] = df_main['Detected CWEs'].fillna('').astype(str)

    cwe_ids = df_main['CWE ID'].unique()

    # Conta match con "Detected CWEs" (per CWE)
    if len(df_main) > 0 and len(cwe_ids) > 0:
        count_matched = {
            cwe_id: df_main['Detected CWEs'].str.contains(rf'\b{re.escape(cwe_id)}\b', regex=True).sum()
            for cwe_id in cwe_ids
        }
        total_matching_cwes = sum(count_matched.values())
    else:
        count_matched = {}
        total_matching_cwes = 0

    # --- Percentuale snippet con almeno un match ---
    total_snippets = len(df_main)  # righe del CSV (header escluso)
    if total_snippets > 0:
        rows_with_match = df_main.apply(
            lambda row: bool(re.search(rf'\b{re.escape(str(row["CWE ID"]))}\b', row["Detected CWEs"])),
            axis=1
        ).sum()
    else:
        rows_with_match = 0
    percent_matched_snippets = (rows_with_match / total_snippets * 100) if total_snippets else 0.0
    # ------------------------------------------------

    # Conteggio locale nel file principale
    count_total_main = df_main['CWE ID'].value_counts().to_dict() if total_snippets else {}

    # Conteggio globale da tutti i file nella cartella
    count_global = {}
    if folder_path and os.path.isdir(folder_path):
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

    # Funzione di sorting robusta (numerico se possibile)
    def _cwe_sort_key(x):
        x = str(x)
        return (0, int(x)) if x.isdigit() else (1, x)

    # Stampa formattata
    header = f"{'CWE ID':<10} | {'Total CWE Scenarios':>17} | {'Total CWE Detections':>22} | {'Matching CWEs':>24}"
    print(header)
    print("-" * len(header))

    for cwe_id in sorted(cwe_ids, key=_cwe_sort_key):
        total_global = count_global.get(cwe_id, 0)
        total_main = count_total_main.get(cwe_id, 0)
        matched = count_matched.get(cwe_id, 0)
        print(f"{cwe_id:<10} | {total_global:>17,} | {total_main:>22,} | {matched:>24,}")

    print("-" * len(header))
    print(f"{'TOTAL Matching CWEs':<10} : {total_matching_cwes:,}")
    print(f"Snippet con almeno un match: {rows_with_match}/{total_snippets} ({percent_matched_snippets:.2f}%)")

    # DataFrame risultato (anche vuoto ma con colonne attese)
    result_df = pd.DataFrame({
        'CWE ID': list(cwe_ids),
        'Total CWE scenarios': [count_global.get(cwe_id, 0) for cwe_id in cwe_ids],
        'Total CWE detection': [count_total_main.get(cwe_id, 0) for cwe_id in cwe_ids],
        'Matches number': [count_matched.get(cwe_id, 0) for cwe_id in cwe_ids]
    })

    return result_df


def check_cwe_match_merged(csv1: str, csv2: str, csv3: str):
    """
    Dati 3 CSV con colonne 'CWE ID' e 'Detected CWEs':
      - stampa per ogni file: matched/total e percentuale
      - stampa la media del numero di snippet con match e la media percentuale
      - ritorna un DataFrame con i dettagli per file + riga MEDIA

    Robusto a file vuoti o con solo header.
    """
    paths = [csv1, csv2, csv3]
    results = []

    for p in paths:
        # Caricamento robusto
        try:
            df = pd.read_csv(p)
        except pd.errors.EmptyDataError:
            df = pd.DataFrame()

        # Se vuoto, registriamo 0/0 (0%)
        if df.empty:
            matched, total, percent = 0, 0, 0.0
        else:
            # Verifica colonne solo se ci sono righe
            if 'CWE ID' not in df.columns or 'Detected CWEs' not in df.columns:
                raise ValueError(f"{p}: il file deve contenere le colonne 'CWE ID' e 'Detected CWEs'")

            # Preprocessing
            df['CWE ID'] = df['CWE ID'].astype(str).str.strip()
            df['Detected CWEs'] = df['Detected CWEs'].fillna('').astype(str)

            total = len(df)
            if total == 0:
                matched, percent = 0, 0.0
            else:
                matched = (df.apply(
                    lambda row: bool(re.search(rf'\b{re.escape(str(row["CWE ID"]))}\b', row["Detected CWEs"])),
                    axis=1
                )).sum()
                percent = (matched / total * 100) if total else 0.0

        results.append({
            "file": Path(p).name,
            "matched_snippets": int(matched),
            "total_snippets": int(total),
            "percent_matched": float(percent)
        })

    # Stampa tabellare
    header = f"{'File':<30} | {'Matched/Total':>15} | {'Percent':>10}"
    print(header)
    print("-" * len(header))
    for r in results:
        ratio = f"{r['matched_snippets']}/{r['total_snippets']}"
        print(f"{r['file']:<30} | {ratio:>15} | {r['percent_matched']:>9.2f}%")
    print("-" * len(header))

    # Medie semplici sui 3 file
    avg_matched = sum(r["matched_snippets"] for r in results) / 3.0
    avg_percent = sum(r["percent_matched"] for r in results) / 3.0

    print(f"Media snippet con match: {avg_matched:.2f}")
    print(f"Media percentuale: {avg_percent:.2f}%")

    # DataFrame di output + riga MEDIA
    df_out = pd.DataFrame(results)
    df_avg = pd.DataFrame([{
        "file": "MEDIA",
        "matched_snippets": avg_matched,
        "total_snippets": None,
        "percent_matched": avg_percent
    }])

    return pd.concat([df_out, df_avg], ignore_index=True)



def analyze_single_feature_significance(csv_path: str, alpha: float = 0.05, top_n: int = 100, verbose: bool = True):
    """
    Reads an aggregated comparison CSV with columns:
        Category, Value, Base, Result
      - Base   = number of items/snippets with the feature (exposure)
      - Result = number of vulnerabilities (events) observed with the feature
                 (can exceed Base because multiple events can occur per snippet)

    Per-(Category, Value) analysis (unchanged):
        - Build a 2x2 table comparing "with feature" vs "without feature".
        - Fisher's Exact when any expected cell < 5 or any observed cell < 5,
          else Chi-square with Yates correction.
        - Benjamini–Hochberg FDR across ALL per-value tests.

    Global (per-Category) omnibus (UPDATED):
        - Test of rate homogeneity across the values of the Category:
          considers Result as event counts and Base as exposure.
          chi2 = sum((O_i - E_i)^2 / E_i) with E_i = Base_i * (sum(Result)/sum(Base))
          df = (#levels_used - 1)
        - Robust to Result > Base and avoids negative cells.

    Prints a clear narrative summary and returns:
        per_value_df (detailed per feature value) and global_df (omnibus per Category).

    Parameters
    ----------
    csv_path : str
        Path to the aggregated metrics CSV.
    alpha : float, default 0.05
        FDR significance threshold for q-values.
    top_n : int, default 100
        How many items to show in the printed “top” sections.
    verbose : bool, default True
        If True, prints a narrative summary to console; if False, suppresses all prints.

    Returns
    -------
    per_value_df : pd.DataFrame
    global_df    : pd.DataFrame
    """
    # --- deps ---
    import numpy as np
    import pandas as pd
    from scipy.stats import chi2_contingency, fisher_exact
    from scipy.stats import chi2 as _chi2

    # --- local logger ---
    def _log(*args, **kwargs):
        if verbose:
            print(*args, **kwargs)

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

    # --- per-value tests (unchanged) ---
    rows = []
    for cat, sub in df.groupby("Category", sort=False):
        N = int(sub["Base"].sum())       # total with-feature items in this category
        V = int(sub["Result"].sum())     # total vulnerabilities in this category
        for _, r in sub.iterrows():
            base = int(r["Base"])
            a = int(r["Result"])         # with feature & vulnerable (events counted)
            b = base - a                 # with feature & safe (can be negative; clamped below)
            c = V - a                    # without feature & vulnerable (events)
            d = (N - base) - c           # without feature & safe (can be negative; clamped below)
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
        _log("No rows to analyze.")
        return per_value_df, pd.DataFrame()

    # FDR
    per_value_df["q_value"] = _bh_fdr(np.nan_to_num(per_value_df["p_value"], nan=1.0))
    per_value_df["Significant"] = per_value_df["q_value"] <= alpha

    # Sorting for reporting
    per_value_df = per_value_df.sort_values(
        ["Significant", "q_value", "Rate_diff", "OddsRatio"],
        ascending=[False, True, False, False]
    ).reset_index(drop=True)

    # --- global (per-category) omnibus UPDATED: Poisson rate homogeneity ---
    global_rows = []
    for cat, sub in df.groupby("Category", sort=False):
        sub = sub.copy()
        sub["Base"] = pd.to_numeric(sub["Base"], errors="coerce")
        sub["Result"] = pd.to_numeric(sub["Result"], errors="coerce")

        # keep only informative rows: exposure > 0 and events >= 0
        sub = sub[(sub["Base"] > 0) & (sub["Result"] >= 0)].copy()

        m = len(sub)
        if m < 2:
            global_rows.append({"Category": cat, "Chi2": np.nan, "df": np.nan, "p_value": np.nan})
            continue

        tot_base = float(sub["Base"].sum())
        tot_vuln = float(sub["Result"].sum())

        if tot_base <= 0:
            global_rows.append({"Category": cat, "Chi2": np.nan, "df": np.nan, "p_value": np.nan})
            continue

        # if no events overall, rates are all zero → no evidence of differences
        if tot_vuln == 0:
            global_rows.append({"Category": cat, "Chi2": 0.0, "df": m - 1, "p_value": 1.0})
            continue

        r = tot_vuln / tot_base
        expected = sub["Base"] * r
        observed = sub["Result"]

        # use only levels with positive expected to avoid division by zero
        mask = expected > 0
        k = int(mask.sum())
        if k < 2:
            global_rows.append({"Category": cat, "Chi2": np.nan, "df": np.nan, "p_value": np.nan})
            continue

        chi2_stat = float((((observed[mask] - expected[mask]) ** 2) / expected[mask]).sum())
        df_glob = int(k - 1)
        p_val = float(_chi2.sf(chi2_stat, df_glob))

        global_rows.append({"Category": cat, "Chi2": chi2_stat, "df": df_glob, "p_value": p_val})

    global_df = pd.DataFrame(global_rows).sort_values("p_value", na_position="last").reset_index(drop=True)

    # === Pretty printing (guarded by verbose) ===
    def pct(x):
        return f"{100*x:.1f}%" if np.isfinite(x) else "NA"

    _log("\n" + "="*80)
    _log("Statistical Analysis — Syntagm Features and Vulnerability")
    _log("="*80)

    # Significant features
    sig = per_value_df[per_value_df["Significant"]]
    if verbose:
        if len(sig):
            _log("\n▶ Significant features (FDR q ≤ {:.2f}) — sorted by q-value".format(alpha))
            for _, r in sig.head(top_n).iterrows():
                direction = "↑ risk" if r["OddsRatio"] > 1 else "↓ risk"
                _log(f"  [{r['Category']}] {r['Value']}: "
                      f"{pct(r['Rate_with'])} vulnerable vs {pct(r['Rate_without'])} baseline | "
                      f"OR={r['OddsRatio']:.2f} ({direction}); "
                      f"p={r['p_value']:.3g}, q={r['q_value']:.3g} ({r['Test']})")
            if len(sig) > top_n:
                _log(f"  ... and {len(sig) - top_n} more significant features.")
        else:
            _log("\n▶ No features reached FDR q ≤ {:.2f}.".format(alpha))

    # Trending but not significant
    notsig = per_value_df[~per_value_df["Significant"]].copy()
    if verbose and len(notsig):
        # rank by absolute rate difference, then p-value
        notsig["_abs_diff"] = notsig["Rate_diff"].abs()
        trending = notsig.sort_values(["_abs_diff", "p_value"], ascending=[False, True]).head(top_n)
        _log("\n⚠ Trending but not significant (largest rate differences; low q but > α)")
        for _, r in trending.iterrows():
            direction = "higher" if r["Rate_diff"] > 0 else "lower"
            _log(f"  [{r['Category']}] {r['Value']}: "
                  f"{pct(r['Rate_with'])} vs {pct(r['Rate_without'])} ({direction} than baseline by {pct(abs(r['Rate_diff']))}); "
                  f"OR={r['OddsRatio']:.2f}, p={r['p_value']:.3g}, q={r['q_value']:.3g} ({r['Test']})")

    # Global category tests (UPDATED description)
    if verbose:
        _log("\n— Global (omnibus) tests per Category —")
        for _, r in global_df.iterrows():
            interp = ("evidence that this Category matters" if (np.isfinite(r["p_value"]) and r["p_value"] < 0.05)
                      else "no strong overall evidence")
            df_txt = int(r["df"]) if np.isfinite(r["df"]) else "NA"
            chi2_txt = f"{r['Chi2']:.2f}" if np.isfinite(r["Chi2"]) else "nan"
            p_txt = f"{r['p_value']:.3g}" if np.isfinite(r["p_value"]) else "nan"
            _log(f"  {r['Category']}: χ²={chi2_txt}, df={df_txt}, p={p_txt} → {interp}")

    return per_value_df, global_df


def analyze_combined_features_significance(csv_path: str, alpha: float = 0.05, top_n: int = 100, verbose: bool = True):
    """
    Analisi per CSV 'combined' con colonne richieste:
      Combination, Features, Base, Result
    Colonne facoltative riportate in output se presenti:
      Granularity, Sentence Index, Syntagm Type, Frequency

    Per combinazione (stratificato per Features):
      - 2×2 test vs il resto delle combinazioni con lo stesso 'Features'
        (Fisher se attesi/osservati < 5, altrimenti Chi² con Yates).
      - BH–FDR su tutte le p dei test per combinazione.

    Omnibus (AGGIORNATO):
      - Test di omogeneità dei tassi (Poisson-like) tra le 'Combination' aggregando su TUTTI i 'Features'.
        * Usa Result come conteggi di eventi e Base come esposizione.
        * Evita safe negativi quando Result > Base.
        * χ² = Σ (O_i - E_i)^2 / E_i, con E_i = Base_i * (Σ Result / Σ Base), df = (#comb_usable - 1).

    Parametri:
      - csv_path : percorso al CSV
      - alpha    : soglia FDR per significatività
      - top_n    : quante righe mostrare nelle stampe riassuntive
      - verbose  : se True (default) stampa un riepilogo; se False non stampa nulla

    Ritorna:
      per_combo_df : risultati per combinazione
      global_df    : una riga con l’omnibus sulle combinazioni
    """
    import numpy as np
    import pandas as pd
    from scipy.stats import chi2_contingency, fisher_exact
    from scipy.stats import chi2 as _chi2

    # --- load & checks ---
    df = pd.read_csv(csv_path)
    required = {"Combination", "Features", "Base", "Result"}
    if not required.issubset(df.columns):
        missing = sorted(required - set(df.columns))
        present = sorted(map(str, df.columns))
        if verbose:
            # Stampa il path del file + dettaglio delle colonne
            print(f"[Schema CSV non valido] File: {csv_path}\n  Mancanti: {missing}\n  Presenti: {present}")
        raise ValueError(f"{csv_path}: CSV must contain columns {sorted(required)} (missing: {missing})")

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
            a = int(r["Result"])         # con la combinazione & vulnerabile (eventi)
            b = base - a                 # con la combinazione & safe (può essere <0 → clamp)
            c = V - a                    # senza la combinazione & vulnerabile (eventi)
            d = (N - base) - c           # senza la combinazione & safe (può essere <0 → clamp)
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
        if verbose:
            print("Nessuna riga da analizzare.")
        return per_combo_df, pd.DataFrame()

    # FDR globale sulle combinazioni
    per_combo_df["q_value"] = _bh_fdr(np.nan_to_num(per_combo_df["p_value"], nan=1.0))
    per_combo_df["Significant"] = per_combo_df["q_value"] <= alpha

    per_combo_df = per_combo_df.sort_values(
        ["Significant", "q_value", "Rate_diff", "OddsRatio"],
        ascending=[False, True, False, False]
    ).reset_index(drop=True)

    # --- OMNIBUS (AGGIORNATO): tassi per Combination aggregando su tutti i Features ---
    agg = (
        df.groupby("Combination", as_index=False)[["Base", "Result"]]
          .sum(numeric_only=True)
    )

    agg = agg[(agg["Base"] > 0) & (agg["Result"] >= 0)].copy()
    m = len(agg)

    if m >= 2 and np.isfinite(agg["Base"].sum()):
        tot_base = float(agg["Base"].sum())
        tot_vuln = float(agg["Result"].sum())

        if tot_base > 0 and tot_vuln > 0:
            r = tot_vuln / tot_base
            expected = agg["Base"] * r
            observed = agg["Result"]
            mask = expected > 0
            k = int(mask.sum())
            if k >= 2:
                chi2_stat = float((((observed[mask] - expected[mask]) ** 2) / expected[mask]).sum())
                dof = int(k - 1)
                p_glob = float(_chi2.sf(chi2_stat, dof))
            else:
                chi2_stat, dof, p_glob = np.nan, np.nan, np.nan
        elif tot_base > 0 and tot_vuln == 0:
            chi2_stat, dof, p_glob = 0.0, int(m - 1), 1.0
        else:
            chi2_stat, dof, p_glob = np.nan, np.nan, np.nan
    else:
        chi2_stat, dof, p_glob = np.nan, np.nan, np.nan

    global_df = pd.DataFrame([{
        "Scope": "All combinations (rate-homogeneity; events=Result, exposure=Base)",
        "Chi2": chi2_stat,
        "df": dof,
        "p_value": p_glob,
        "Combinations_used": int(m)
    }])

    # === Pretty printing (opzionale) ===
    if verbose:
        def pct(x):
            import numpy as np
            return f"{100*x:.1f}%" if np.isfinite(x) else "NA"

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

        print("\n— Omnibus sulle combinazioni (aggregato su tutti i Features) —")
        print("  (Rate-homogeneity test: events=Result, exposure=Base)")
        interp = ("evidenza che alcune combinazioni differiscano nel tasso di vulnerabilità"
                  if (np.isfinite(p_glob) and p_glob < 0.05)
                  else "nessuna forte evidenza complessiva")
        chi2_txt = f"{chi2_stat:.2f}" if np.isfinite(chi2_stat) else "nan"
        df_txt = int(dof) if np.isfinite(dof) else "NA"
        p_txt = f"{p_glob:.3g}" if np.isfinite(p_glob) else "nan"
        print(f"  χ²={chi2_txt}, df={df_txt}, p={p_txt} → {interp} (Combinations used: {int(m) if m==m else 'NA'})")

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


def compute_vulnerable_snippets(
    csv_path: str,
    total_snippets: int,
    header: Union[bool, str] = "auto",
) -> float:
    """
    Conta gli snippet vulnerabili (righe non vuote nel CSV, opzionalmente
    escludendo l'header) e stampa:
      - il totale degli snippet vulnerabili
      - la percentuale di snippet vulnerabili sul totale degli snippet

    Ritorna comunque la frazione (0–1) per compatibilità.

    Parametri
    ----------
    csv_path : str
        Percorso al CSV che contiene le istanze (una per riga).
    total_snippets : int
        Numero totale di snippet (denominatore).
    header : bool | "auto", opzionale
        Gestione dell'header:
        - True  -> la prima riga non vuota è un header e viene esclusa
        - False -> nessun header
        - "auto" (default) -> tenta il rilevamento con csv.Sniffer

    Ritorna
    -------
    float
        Frazione snippet vulnerabili / totale_snippet.
    """
    if total_snippets <= 0:
        raise ValueError("total_snippets must be a positive integer.")

    # Determina la presenza dell'header
    has_header = False
    with open(csv_path, "r", encoding="utf-8-sig", newline="") as f:
        sample = f.read(2048)
        f.seek(0)
        if header == "auto":
            try:
                has_header = csv.Sniffer().has_header(sample)
            except Exception:
                has_header = True  # default prudente
        else:
            has_header = bool(header)

        reader = csv.reader(f)
        non_empty_rows = []
        for row in reader:
            # considera vuote le righe con tutte le celle vuote
            if not row or not any((cell or "").strip() for cell in row):
                continue
            non_empty_rows.append(row)

    cwe_rows = max(len(non_empty_rows) - (1 if has_header and non_empty_rows else 0), 0)
    rate = cwe_rows / total_snippets
    percent = rate * 100.0

    # Stampa SOLO quanto richiesto
    print(f"Snippet vulnerabili totali: {cwe_rows}")
    print(f"Percentuale snippet vulnerabili: {percent:.2f}%")

    return rate


def compute_vulnerable_snippets_merged(
    csv_paths: Sequence[str],
    total_snippets: Union[int, Sequence[int]],
    header: Union[bool, str] = "auto",
) -> Tuple[int, float, float]:
    """
    Dati 3 CSV con la medesima struttura, per ciascuno:
      - conta le righe non vuote (header escluso se presente);
      - calcola la percentuale sul totale fornito;
      - calcola il tasso CWE/snippet (= vulnerabili / totale).

    Stampa SOLO:
      - il numero medio (arrotondato) di snippet vulnerabili;
      - la percentuale media di snippet vulnerabili.

    Ritorna (invariato):
      - media intera del numero di snippet vulnerabili (int);
      - percentuale media (float);
      - tasso medio CWE/snippet (float).
    """
    if len(csv_paths) != 3:
        raise ValueError("Fornire esattamente 3 CSV in 'csv_paths'.")

    # Normalizza i totali per file
    if isinstance(total_snippets, int):
        totals: List[int] = [total_snippets, total_snippets, total_snippets]
    else:
        totals = list(total_snippets)
        if len(totals) != 3:
            raise ValueError("Se si passano totali per-file, fornirne esattamente 3.")
    if any(t <= 0 for t in totals):
        raise ValueError("Ogni valore di 'total_snippets' deve essere un intero positivo.")

    counts: List[int] = []
    percentages: List[float] = []
    rates: List[float] = []

    # Per ciascun CSV: conta righe non vuote, escludendo l'eventuale header
    for path, tot in zip(csv_paths, totals):
        has_header = False
        with open(path, "r", encoding="utf-8-sig", newline="") as f:
            sample = f.read(2048)
            f.seek(0)
            if header == "auto":
                try:
                    has_header = csv.Sniffer().has_header(sample)
                except Exception:
                    has_header = True  # default prudente
            else:
                has_header = bool(header)

            reader = csv.reader(f)
            non_empty_rows = []
            for row in reader:
                if not row or not any((cell or "").strip() for cell in row):
                    continue
                non_empty_rows.append(row)

        vulnerable_rows = max(len(non_empty_rows) - (1 if has_header and non_empty_rows else 0), 0)
        rate = vulnerable_rows / tot
        pct = rate * 100.0

        counts.append(vulnerable_rows)
        percentages.append(pct)
        rates.append(rate)

    # Medie finali
    mean_count = sum(counts) / 3.0
    mean_count_int = int(Decimal(mean_count).quantize(0, rounding=ROUND_HALF_UP))
    mean_percentage = sum(percentages) / 3.0
    mean_rate = sum(rates) / 3.0

    # Stampa SOLO i valori medi richiesti
    print(f"Snippet vulnerabili medi: {mean_count_int}")
    print(f"Percentuale media snippet vulnerabili: {mean_percentage:.2f}%")

    return mean_count_int, mean_percentage, mean_rate


def collect_detected_cwes_merged(
    csv_path_1: str,
    csv_path_2: str,
    csv_path_3: str,
    column: str = "Detected CWEs",
    separator: str = ",",
    top_k: int = 5,
    quiet: bool = False,   # come nella funzione base
    silent: bool = False,  # se True, non stampa nulla
) -> float:
    """
    Legge tre CSV (csv_path_1, csv_path_2, csv_path_3), estrae i CWE dalla colonna `column`
    (separati da `separator`) e calcola:
      - la TOP-K (default 5) delle CWE in base alla MEDIA delle loro cardinalità sui 3 CSV
        (se un CWE non compare in un file, vale 0 in quel file).
      - la MEDIA del numero TOTALE di CWE sui 3 CSV (somma occorrenze per file, poi media sui 3).

    STAMPA (solo se `silent` è False e `quiet` è False):
      - la classifica Top-K con la media delle occorrenze
      - la media del numero totale di CWE sui 3 CSV

    RITORNA:
      - la media del numero TOTALE di CWE sui 3 CSV (float)
    """
    def _count_cwes_in_csv(csv_path: str) -> Counter:
        counts = Counter()
        with open(csv_path, newline="", encoding="utf-8-sig") as f:
            reader = csv.DictReader(f)
            if not reader.fieldnames or column not in reader.fieldnames:
                raise ValueError(
                    f"Colonna '{column}' non trovata in {csv_path}. Colonne disponibili: {reader.fieldnames}"
                )
            for row in reader:
                field = (row.get(column) or "").strip()
                if not field:
                    continue
                for token in field.split(separator):
                    cwe = token.strip()
                    if cwe:
                        counts[cwe] += 1
        return counts

    # Conta per ciascun CSV
    c1 = _count_cwes_in_csv(csv_path_1)
    c2 = _count_cwes_in_csv(csv_path_2)
    c3 = _count_cwes_in_csv(csv_path_3)

    # Unione di tutti i CWE
    all_cwes = set(c1) | set(c2) | set(c3)

    # Media delle cardinalità per ogni CWE (considerando 0 dove assente)
    averaged: List[Tuple[str, float]] = []
    for cwe in all_cwes:
        mean_val = (c1.get(cwe, 0) + c2.get(cwe, 0) + c3.get(cwe, 0)) / 3.0
        averaged.append((cwe, mean_val))

    # Ordina per media desc, poi CWE asc
    averaged.sort(key=lambda kv: (-kv[1], kv[0]))

    top = averaged[:top_k]

    # Media del numero TOTALE di CWE sui 3 CSV
    t1 = sum(c1.values())
    t2 = sum(c2.values())
    t3 = sum(c3.values())
    mean_total = (t1 + t2 + t3) / 3.0

    # Stampa solo ciò che è richiesto
    if not silent and not quiet:
        if top:
            max_cwe_len = max(len(cwe) for cwe, _ in top)
            header = f"{'#':>4}  {'CWE':<{max_cwe_len}}  {'Media occorrenze':>17}"
            print(header)
            print("-" * len(header))
            for i, (cwe, avg) in enumerate(top, start=1):
                print(f"{i:>4}  {cwe:<{max_cwe_len}}  {avg:>17.2f}")
        else:
            print("Nessun CWE trovato nei tre CSV.")

        print(f"\nMedia del numero TOTALE di CWE sui 3 CSV: {mean_total:.2f}")

    return mean_total



def single_feature_frequency_mean_to_csv(csv_a: str,
                                         csv_b: str,
                                         csv_c: str,
                                         out_csv: str,
                                         sep: str = ",",
                                         decimal: str = ".",
                                         encoding: str = "utf-8",
                                         sort: bool = True) -> pd.DataFrame:
    """
    Legge tre CSV con colonne almeno:
      'Category', 'Value', 'Frequency', 'Base', 'Result'
    e salva un nuovo CSV con colonne in questo ordine:
      ['Category', 'Value', 'Base', 'Result', 'Frequency']

    Regole:
      - Si considerano SOLO le coppie (Category, Value) comuni a TUTTI e tre i file.
      - 'Frequency' è la media delle tre Frequency e viene SEMPRE stampata come "00.00%".
      - 'Result' è la media delle tre Result e viene SEMPRE arrotondata all'intero.
      - 'Base' deve coincidere nei tre CSV per la stessa coppia; altrimenti errore.
    """

    def _to_float(series: pd.Series, decimal: str, treat_percent: bool = True) -> tuple[pd.Series, bool]:
        s_raw = series.astype(str)
        s = s_raw.str.strip()

        had_percent = False
        if treat_percent:
            had_percent = s.str.contains("%", regex=False, na=False)
            s = s.str.replace("%", "", regex=False)

        if decimal == ",":
            s = s.str.replace(".", "", regex=False)   # migliaia
            s = s.str.replace(",", ".", regex=False)  # decimali
        else:
            s = s.str.replace(",", "", regex=False)   # migliaia

        out = pd.to_numeric(s, errors="coerce")
        if treat_percent:
            out = out.where(~had_percent, out / 100.0)
            return out, bool(had_percent.any())
        else:
            return out, False

    def _prep(path: str) -> pd.DataFrame:
        df = pd.read_csv(path, sep=sep, decimal=decimal, encoding=encoding)
        required = {"Category", "Value", "Frequency", "Base", "Result"}
        missing = required - set(df.columns)
        if missing:
            raise ValueError(f"{path}: mancano le colonne {missing}")

        df["Category"] = df["Category"].astype(str).str.strip()
        df["Value"]    = df["Value"].astype(str).str.strip()

        df["Frequency"], _ = _to_float(df["Frequency"], decimal, treat_percent=True)
        df["Result"],    _ = _to_float(df["Result"],    decimal, treat_percent=True)   # input può avere %
        df["Base"],      _ = _to_float(df["Base"],      decimal, treat_percent=False)  # Base non % in input

        df = df.dropna(subset=["Frequency", "Result", "Base"])

        # consolida eventuali duplicati
        df = (df.groupby(["Category", "Value"], as_index=False)
                .agg(Frequency=("Frequency", "mean"),
                     Result=("Result", "mean"),
                     Base=("Base", "mean")))
        return df

    a = _prep(csv_a)
    b = _prep(csv_b)
    c = _prep(csv_c)

    merged = (a.merge(b, on=["Category", "Value"], how="inner", suffixes=("_a", "_b"))
                .merge(c, on=["Category", "Value"], how="inner"))

    merged = merged.rename(columns={"Frequency": "Frequency_c",
                                    "Result": "Result_c",
                                    "Base": "Base_c"})

    if merged.empty:
        a_keys = set(zip(a["Category"], a["Value"]))
        b_keys = set(zip(b["Category"], b["Value"]))
        c_keys = set(zip(c["Category"], c["Value"]))
        raise ValueError(
            "Nessuna coppia (Category, Value) in comune tra tutti e tre i file.\n"
            f"A∩B: {len(a_keys & b_keys)}  A∩C: {len(a_keys & c_keys)}  B∩C: {len(b_keys & c_keys)}  A∩B∩C: 0"
        )

    # Coerenza Base
    tol = 1e-9
    mismatch_mask = ~(
        (merged["Base_a"] - merged["Base_b"]).abs().le(tol) &
        (merged["Base_a"] - merged["Base_c"]).abs().le(tol)
    )
    if mismatch_mask.any():
        bad = merged.loc[mismatch_mask, ["Category", "Value", "Base_a", "Base_b", "Base_c"]].head(10)
        raise ValueError(
            "Valori 'Base' non coerenti tra i tre file per alcune coppie (Category, Value). "
            "Esempi (prime 10):\n" + bad.to_string(index=False)
        )

    # Base coerente
    merged["Base"] = merged["Base_a"]

    # Medie
    merged["Frequency"] = merged[["Frequency_a", "Frequency_b", "Frequency_c"]].mean(axis=1)
    merged["Result"]    = merged[["Result_a", "Result_b", "Result_c"]].mean(axis=1)

    out = merged[["Category", "Value", "Base", "Result", "Frequency"]]

    if sort:
        out = out.sort_values(["Category", "Value"]).reset_index(drop=True)

    # --- formattazione output ---
    def _format_number(x: float, decimal: str, sig: int = 6) -> str:
        s = f"{x:.{sig}g}"
        if decimal == ",":
            s = s.replace(".", ",")
        return s

    # Base: numero secco
    def _fmt_base(x: float) -> str:
        if pd.isna(x):
            return ""
        if abs(x - round(x)) < 1e-9:
            return f"{int(round(x))}"
        return _format_number(float(x), decimal)

    out["Base"] = out["Base"].apply(_fmt_base)

    # Result: media arrotondata all'intero (half-away-from-zero)
    def _round_half_away_from_zero(v: float) -> int:
        if pd.isna(v):
            return ""
        return int(math.floor(v + 0.5)) if v >= 0 else int(math.ceil(v - 0.5))

    out["Result"] = out["Result"].apply(_round_half_away_from_zero).astype(str)

    # Frequency: sempre "00.00%"
    def _fmt_pct(x: float) -> str:
        val = x * 100.0
        s = f"{val:.2f}"
        if decimal == ",":
            s = s.replace(".", ",")
        return s + "%"

    out["Frequency"] = out["Frequency"].apply(_fmt_pct)

    # scrivi CSV
    Path(out_csv).parent.mkdir(parents=True, exist_ok=True)
    out.to_csv(out_csv, index=False, sep=sep, encoding=encoding)

    return out


def combined_feature_frequency_mean_to_csv(csv_a: str,
                                           csv_b: str,
                                           csv_c: str,
                                           csv_out: str,
                                           sep: str = ",",
                                           decimal: str = ".",
                                           encoding: str = "utf-8",
                                           sort: bool = True) -> pd.DataFrame:
    """
    Crea un CSV 'csv_out' con colonne:
      ['Combination','Features','Granularity','Sentence Index','Syntagm Type', 'Base','Result','Frequency']

    - Frequency = media (0–1) delle tre fonti, formattata come 00.00% (o 00,00%) nel CSV.
    - Result     = media dei tre CSV (normalizzata come Frequency se espressa in %), poi arrotondata all'intero.
    - 'Sentence Index' scritto come intero.
    - I metadati (Features, Granularity, Sentence Index, Syntagm Type) sono presi da csv_a (primo valore non nullo).
    - 'Base' deve essere identica nei tre CSV per ogni 'Combination'; in caso contrario si solleva un errore.
    """

    META_COLS = ["Features", "Granularity", "Sentence Index", "Syntagm Type"]

    def _normalize_combo(s: str) -> str:
        s = unicodedata.normalize("NFKC", str(s)).strip()
        s = " ".join(s.split())
        return s

    def _parse_value(series: pd.Series) -> pd.Series:
        """
        Converte valori numerici/percentuali:
        - 0.42 / 0,42 -> 0.42
        - 42% / 42,0 % -> 0.42
        """
        raw = series.astype(str)
        has_percent = raw.str.contains("%", na=False)
        clean = raw.str.replace("%", "", regex=False).str.strip()
        clean = clean.str.replace(",", ".", regex=False)
        num = pd.to_numeric(clean, errors="coerce")
        # se in almeno una cella della colonna compaiono '%', interpretiamo la colonna come percentuale
        num = num / 100.0 if has_percent.any() else num
        return num

    def _prep(path: str) -> pd.DataFrame:
        df = pd.read_csv(path, sep=sep, decimal=decimal, encoding=encoding)

        required = {"Combination", "Frequency", "Result"}
        missing = required - set(df.columns)
        if missing:
            raise ValueError(f"{path}: mancano le colonne {missing}")

        df["Combination"] = df["Combination"].map(_normalize_combo)
        df["Frequency"] = _parse_value(df["Frequency"])
        df["Result"] = _parse_value(df["Result"])

        if "Sentence Index" in df.columns:
            df["Sentence Index"] = pd.to_numeric(df["Sentence Index"], errors="coerce").astype("Int64")

        df = df.dropna(subset=["Frequency", "Result"])
        if df.empty:
            raise ValueError(f"{path}: dopo il parsing, nessuna riga valida in 'Frequency'/'Result'.")

        agg = {"Frequency": "mean", "Result": "mean"}
        if "Base" in df.columns:
            agg["Base"] = "first"
        for col in META_COLS:
            if col in df.columns:
                agg[col] = "first"

        df = df.groupby("Combination", as_index=False).agg(agg)

        rename_map = {"Frequency": f"Frequency_{Path(path).stem}",
                      "Result":    f"Result_{Path(path).stem}"}
        if "Base" in df.columns:
            rename_map["Base"] = f"Base_{Path(path).stem}"

        df = df.rename(columns=rename_map)
        return df

    a = _prep(csv_a)
    b = _prep(csv_b)
    c = _prep(csv_c)

    merged = a.merge(b, on="Combination", how="inner").merge(c, on="Combination", how="inner")
    if merged.empty:
        only_ab = a.merge(b, on="Combination", how="inner")
        only_ac = a.merge(c, on="Combination", how="inner")
        only_bc = b.merge(c, on="Combination", how="inner")
        raise ValueError(
            "Nessuna 'Combination' in comune tra tutti e tre i file.\n"
            f"- Intersezione A∩B: {len(only_ab)}\n"
            f"- Intersezione A∩C: {len(only_ac)}\n"
            f"- Intersezione B∩C: {len(only_bc)}\n"
            "Controlla spazi/maiuscole/punteggiatura delle 'Combination'."
        )

    # media finale (0–1) per Frequency
    freq_cols = [c for c in merged.columns if c.startswith("Frequency_")]
    merged["Frequency"] = merged[freq_cols].mean(axis=1)

    # media per Result -> arrotonda all'intero
    result_cols = [c for c in merged.columns if c.startswith("Result_")]
    merged["Result"] = merged[result_cols].mean(axis=1)
    merged["Result"] = merged["Result"].round().astype("Int64")  # intero approssimato, preserva NA

    # 'Base' unificata e coerente
    base_cols = [c for c in merged.columns if c.startswith("Base_")]
    if base_cols:
        def _pick_and_check(row):
            vals = [row[col] for col in base_cols if pd.notna(row[col])]
            if not vals:
                return pd.NA
            uniq = set(map(str, vals))
            if len(uniq) > 1:
                raise ValueError(
                    f"Incongruenza su 'Base' per Combination='{row['Combination']}': {vals}"
                )
            return vals[0]
        merged["Base"] = merged.apply(_pick_and_check, axis=1)
    else:
        merged["Base"] = pd.NA

    # metadati e tipi
    for col in META_COLS:
        if col not in merged.columns:
            merged[col] = pd.NA
    merged["Sentence Index"] = pd.to_numeric(merged["Sentence Index"], errors="coerce").astype("Int64")

    # ORDINE COLONNE: Base, Result, Frequency come ultime 3
    out_cols = ["Combination"] + META_COLS + ["Base", "Result", "Frequency"]
    out = merged[out_cols]

    if sort:
        out = out.sort_values(["Combination"]).reset_index(drop=True)

    # formatter percentuale solo per 'Frequency' al momento della scrittura
    def _format_pct(x: float) -> str:
        s = f"{x * 100:.2f}%"
        return s.replace(".", ",") if decimal == "," else s

    to_write = out.copy()
    to_write["Frequency"] = to_write["Frequency"].map(lambda v: _format_pct(float(v)) if pd.notna(v) else "")
    # 'Result' resta intero; gli Int64 vengono scritti come interi (celle vuote per NA)

    to_write.to_csv(csv_out, sep=sep, index=False, encoding=encoding)

    # riepilogo console
    for _, row in out.iterrows():
        freq_str = _format_pct(float(row["Frequency"])) if pd.notna(row["Frequency"]) else ""
        print(f"{row['Combination']}: Result={row['Result']} | Frequency={freq_str}")

    return out


def cwe_scenarios_frequency_mean(csv_a: str,
                                 csv_b: str,
                                 csv_c: str,
                                 out_csv: str,
                                 sep: str = ",",
                                 decimal: str = ".",
                                 encoding: str = "utf-8",
                                 sort: bool = True) -> pd.DataFrame:
    """
    Legge tre CSV con colonne 'CWE', 'Frequency' e 'Base' (opzionale: 'Result'),
    e salva un CSV con ['CWE','Base','Result','Frequency'].

    - Frequency (output): media delle tre frequenze (in frazione) formattata '00.00%'.
    - Result (output): vera media intera (half-up) dei tre 'Result' per CWE;
      se mancano, deriva per-file da Frequency*100 prima di mediare.
    - Base: deve coincidere tra i file per ciascun CWE (altrimenti errore).
    """

    def _norm_cwe_val(x: str) -> str | None:
        s = str(x).strip()
        m = re.search(r"(\d+)", s)
        return f"CWE-{int(m.group(1))}" if m else None

    def _parse_frequency_col(s: pd.Series) -> pd.Series:
        t = s.astype(str).str.strip()
        is_pct = t.str.contains("%", na=False)
        t = t.str.replace("%", "", regex=False)
        if decimal != ".":
            t = t.str.replace(decimal, ".", regex=False)
        vals = pd.to_numeric(t, errors="coerce")
        return pd.Series(np.where(is_pct, vals/100, vals), index=s.index)  # frazione 0–1

    def _parse_result_col(s: pd.Series) -> pd.Series:
        t = s.astype(str).str.strip()
        is_pct = t.str.contains("%", na=False)
        t = t.str.replace("%", "", regex=False)
        if decimal != ".":
            t = t.str.replace(decimal, ".", regex=False)
        vals = pd.to_numeric(t, errors="coerce")
        return pd.Series(vals, index=s.index)  # 0–100 (float) o NA

    def _half_up(x) -> pd.Series:
        s = pd.Series(x, dtype="Float64")  # consente NA
        return s.add(0.5).apply(np.floor).astype("Int64")

    def _prep(path: str) -> pd.DataFrame:
        df = pd.read_csv(path, sep=sep, decimal=decimal, encoding=encoding)
        required = {"CWE", "Frequency", "Base"}
        missing = required - set(df.columns)
        if missing:
            raise ValueError(f"{path}: mancano le colonne {missing}")

        df = df.copy()
        df.loc[:, "CWE"] = df["CWE"].map(_norm_cwe_val)
        df.loc[:, "Frequency"] = _parse_frequency_col(df["Frequency"])
        if "Result" in df.columns:
            df.loc[:, "_ResultParsed"] = _parse_result_col(df["Result"])
        else:
            df.loc[:, "_ResultParsed"] = pd.Series([pd.NA] * len(df), dtype="Float64")

        df = df.dropna(subset=["CWE", "Frequency", "Base"]).copy()

        # Aggregazioni per CWE
        g = df.groupby("CWE", sort=False)
        freq_mean = g["Frequency"].mean()                            # frazione 0–1 (Series indicizzata da CWE)
        res_mean  = g["_ResultParsed"].mean()                        # 0–100 float o NA
        base_agg  = g["Base"].agg(lambda s: s.dropna().astype(str).unique()[0])

        # Riempie i Result mancanti derivando dal file: Frequency*100 half-up
        derived_from_freq = _half_up(freq_mean * 100).astype("Float64")
        res_mean = res_mean.astype("Float64").fillna(derived_from_freq)

        stem = Path(path).stem

        # *** EVITA ambiguità: costruisci il DF con indice pulito e senza riallineamento ***
        out = pd.DataFrame({
            "CWE": freq_mean.index.astype(str)              # colonna esplicita
        })
        out[f"Frequency_{stem}"] = freq_mean.to_numpy()     # nessun allineamento per indice
        out[f"Base_{stem}"]      = base_agg.to_numpy()
        out[f"Result_{stem}"]    = _half_up(res_mean).to_numpy()

        # assicurati che non ci sia un indice nominato "CWE"
        out.index.name = None
        return out

    a = _prep(csv_a)
    b = _prep(csv_b)
    c = _prep(csv_c)

    # Merge sui CWE (solo colonne, nessun indice CWE)
    merged = a.merge(b, on="CWE", how="inner").merge(c, on="CWE", how="inner")
    if merged.empty:
        raise ValueError("Nessun 'CWE' in comune tra tutti e tre i file (controlla formati/coerenza dei CWE).")

    # Frequenze: media su frazioni (0–1)
    freq_cols = [col for col in merged.columns if col.startswith("Frequency_")]
    merged.loc[:, "Frequency"] = merged[freq_cols].mean(axis=1)

    # Base: deve coincidere
    base_cols = [col for col in merged.columns if col.startswith("Base_")]
    base_equal = merged[base_cols].apply(lambda r: len(set(map(str, r))) == 1, axis=1)
    if not base_equal.all():
        bad = merged.loc[~base_equal, ["CWE"] + base_cols]
        raise ValueError(
            "Valori 'Base' non coerenti tra i tre file per alcuni CWE. "
            f"Righe interessate:\n{bad.to_string(index=False)}"
        )
    merged.loc[:, "Base"] = merged[base_cols[0]].astype(str)

    # Result: vera media dei tre Result_* (0–100), half-up all'intero
    result_cols = [col for col in merged.columns if col.startswith("Result_")]
    result_mean = merged[result_cols].astype("Float64").mean(axis=1)
    merged.loc[:, "Result"] = _half_up(result_mean)

    # Fallback se NA (non dovrebbe più succedere)
    na_mask = merged["Result"].isna()
    if na_mask.any():
        merged.loc[na_mask, "Result"] = _half_up(merged.loc[na_mask, "Frequency"] * 100)

    out = merged.loc[:, ["CWE", "Base", "Result", "Frequency"]].copy()
    if sort:
        out = out.sort_values(["CWE"], kind="stable").reset_index(drop=True)

    # Frequency -> '00.00%'
    out.loc[:, "Frequency"] = (out["Frequency"] * 100).map(lambda x: f"{x:.2f}%")

    Path(out_csv).parent.mkdir(parents=True, exist_ok=True)
    out.to_csv(out_csv, index=False, sep=sep, encoding=encoding)

    return out


def single_feature_statistical_analysis_merged(
    csv_path_1,
    csv_path_2,
    csv_path_3,
    alpha=0.05,
    mostra_non_significativi_vicini=False,  # non usato qui: la nuova funzione riporta solo le intersezioni significative
    k_vicini=5,
    min_events=0
):
    """
    Analizza tre CSV (stessa struttura: colonne Category, Value, Base, Result) e riporta:
      1) OMNIBUS: feature che risultano significative (FDR) in TUTTI e 3 i file.
      2) PER-VALORE: (Category, Value) significativi (FDR) in TUTTI e 3 i file.

    NOVITÀ: per ogni singolo file, l'analisi PER-VALORE è eseguita SOLO sulle feature
    il cui OMNIBUS (dopo FDR) è significativo; altrimenti la feature viene saltata.

    Per gli elementi COMUNI calcola aggregati “logicamentente corretti”:
      - P-value combinato con metodo di Fisher (evita la media semplice di p).
      - OMNIBUS: N_tot combinato (somma), Cramér’s V media pesata su N_tot.
      - PER-VALORE: pooling dei conteggi (somma di Base/Result sia per il valore sia per il “resto”),
                    tassi pooled, RR pooled = rate_valore_pooled / rate_resto_pooled,
                    media geometrica dei RR come metrica ausiliaria.

    Ritorna un dict con:
        {
          'omnibus_common': DataFrame,
          'per_value_common': DataFrame,
          'details': {
              'single_runs': [
                  {'omnibus': df1_omni, 'per_value': df1_perval},  # per ciascun file
                  ...
              ]
          }
        }
    e stampa anche un breve report testuale.

    Note:
    - Usa Barnard’s exact test (two-sided, NO odds ratio) per i test per-valore.
    - FDR (Benjamini–Hochberg) applicata all’interno di ciascun singolo file come nel comportamento originale.
    - L’intersezione “comune” è fatta sulle entità risultate significative (dopo FDR) in ciascun file.
    """
    import pandas as pd
    import numpy as np

    # ---------- util ----------
    def bh_fdr(pvals):
        p = np.asarray(pvals, dtype=float)
        n = len(p)
        order = np.argsort(p)
        ranked = p[order]
        adj = np.empty(n)
        prev = 1.0
        for i in range(n - 1, -1, -1):
            adj[i] = min(prev, ranked[i] * n / (i + 1))
            prev = adj[i]
        out = np.empty(n); out[order] = adj
        return out

    try:
        from scipy.stats import barnard_exact as _barnard_exact  # type: ignore
        from scipy.stats import chi2
    except Exception as e:
        raise ImportError(
            "SciPy con 'barnard_exact' è richiesto. Installa/aggiorna SciPy."
        ) from e

    # ---------- helper: p-value Barnard (NO OR) ----------
    ALT = "two-sided"
    def p_value_no_or(k1, n1, k2, n2):
        if n1 <= 0 or n2 <= 0:
            return np.nan
        import numpy as _np
        table = _np.array([[k1, n1 - k1],
                           [k2, n2 - k2]], dtype=int)
        res = _barnard_exact(table, alternative=ALT)
        try:
            p = float(res.pvalue)
        except AttributeError:
            _, p = res
            p = float(p)
        return p

    # ---------- OMNIBUS permutazionale ----------
    rng = np.random.default_rng(None)
    _B_PERM = 5000

    def _chi2_stat_from_counts(successes, bases, K=None):
        successes = successes.astype(float)
        bases = bases.astype(float)
        N = bases.sum()
        if N <= 0:
            return np.nan, np.nan, (np.nan, np.nan)
        if K is None:
            K = successes.sum()
        p = K / N
        exp_s = bases * p
        exp_f = bases * (1 - p)
        with np.errstate(divide='ignore', invalid='ignore'):
            chi_s = (successes - exp_s) ** 2 / exp_s
            chi_f = ((bases - successes) - exp_f) ** 2 / exp_f
            stat = np.nansum(chi_s) + np.nansum(chi_f)
        dof = (2 - 1) * (len(bases) - 1)
        exp_min_s = float(np.nanmin(exp_s)) if len(exp_s) else np.nan
        exp_min_f = float(np.nanmin(exp_f)) if len(exp_f) else np.nan
        return float(stat), int(dof), (exp_min_s, exp_min_f)

    def _perm_pvalue(successes, bases, B=_B_PERM):
        bases = bases.astype(int)
        successes = successes.astype(int)
        N = int(bases.sum()); K = int(successes.sum())
        if N <= 0:
            return np.nan, np.nan, (np.nan, np.nan), np.nan
        if (bases < 0).any() or (successes < 0).any() or (successes > bases).any():
            return np.nan, np.nan, (np.nan, np.nan), np.nan

        stat_obs, dof, exp_mins = _chi2_stat_from_counts(successes, bases, K)
        if not np.isfinite(stat_obs):
            return np.nan, stat_obs, exp_mins, np.nan

        # Cramér’s V (r=2)
        c = len(bases)
        denom = N * max(1, min(2 - 1, c - 1))
        V = float(np.sqrt(stat_obs / denom)) if (denom > 0 and np.isfinite(stat_obs)) else np.nan

        # Precomputo split per shuffle
        idx_cuts = np.cumsum(bases)[:-1]
        vec = np.zeros(N, dtype=np.int8); vec[:K] = 1

        exceed = 0
        for _ in range(B):
            rng.shuffle(vec)
            parts = np.split(vec, idx_cuts)
            perm_successes = np.fromiter((p.sum() for p in parts), dtype=np.int64, count=len(parts))
            stat_perm, _, _ = _chi2_stat_from_counts(perm_successes, bases, K)
            if np.isfinite(stat_perm) and stat_perm >= stat_obs:
                exceed += 1

        pval = (exceed + 1.0) / (B + 1.0)
        return float(pval), float(stat_obs), exp_mins, V

    # ---------- analisi singolo CSV -> (omnibus_df, per_value_df) ----------
    def _analyze_one(csv_path):
        df = pd.read_csv(csv_path)
        need = {"Category", "Value", "Base", "Result"}
        if not need.issubset(df.columns):
            raise ValueError(f"Mancano colonne: {need - set(df.columns)}")
        df = df.copy()
        df["Base"] = pd.to_numeric(df["Base"], errors="coerce").fillna(0).astype(int)
        df["Result"] = pd.to_numeric(df["Result"], errors="coerce").fillna(0).astype(int)
        df["Result"] = df[["Result", "Base"]].min(axis=1).clip(lower=0)
        df["Rate"] = np.where(df["Base"] > 0, df["Result"] / df["Base"], np.nan)

        # OMNIBUS
        omni_rows = []
        for feat, g in df.groupby("Category", sort=False):
            bases = g["Base"].to_numpy()
            succs = g["Result"].to_numpy()
            if np.sum(bases) <= 0:
                p = np.nan; stat = np.nan; dof = 0; n_tot = int(np.sum(bases)); exp_mins = (np.nan, np.nan); V = np.nan
            else:
                p, stat, exp_mins, V = _perm_pvalue(succs, bases, B=_B_PERM)
                dof = (2 - 1) * (len(bases) - 1)
                n_tot = int(np.sum(bases))
            omni_rows.append({
                "Category": feat,
                "Levels": int(len(bases)),
                "N_tot": n_tot,
                "chi2_stat": stat,
                "dof": int(dof),
                "p_omnibus_raw": p,
                "CramersV": V,
            })
        omnibus_df = pd.DataFrame(omni_rows) if len(omni_rows) else pd.DataFrame(
            columns=["Category","Levels","N_tot","chi2_stat","dof","p_omnibus_raw","CramersV"]
        )
        if len(omnibus_df):
            mask = omnibus_df["p_omnibus_raw"].notna()
            omnibus_df["p_omnibus_adj"] = np.nan
            if mask.any():
                omnibus_df.loc[mask, "p_omnibus_adj"] = bh_fdr(omnibus_df.loc[mask, "p_omnibus_raw"].values)
            omnibus_df["Omnibus_significativo_FDR"] = omnibus_df["p_omnibus_adj"] < alpha
        else:
            omnibus_df["Omnibus_significativo_FDR"] = pd.Series(dtype=bool)

        # ====== NOVITÀ: per-value solo se OMNIBUS è significativo (dopo FDR) ======
        sig_omni_feats = set(
            omnibus_df.loc[omnibus_df["Omnibus_significativo_FDR"] == True, "Category"]
        )

        # PER-VALORE (solo feature con omnibus significativo)
        pv_rows = []
        if len(sig_omni_feats) > 0:
            for feat, g in df.groupby("Category", sort=False):
                if feat not in sig_omni_feats:
                    continue  # SALTA la feature perché l'OMNIBUS non è significativo

                base_tot = int(g["Base"].sum())
                res_tot  = int(g["Result"].sum())
                tmp = []
                skipped = 0
                for _, r in g.iterrows():
                    n = int(r["Base"]); k = int(r["Result"])
                    if k < min_events:
                        skipped += 1
                        continue
                    base_oth = base_tot - n
                    res_oth  = res_tot - k
                    p_val = (k / n) if n > 0 else np.nan
                    p_oth = (res_oth / base_oth) if base_oth > 0 else np.nan
                    if n == 0 or base_oth == 0:
                        p_raw = np.nan
                        rr = np.nan
                        delta_abs = np.nan
                    else:
                        p_raw = p_value_no_or(k, n, res_oth, base_oth)
                        if p_oth == 0:
                            rr = np.inf if (p_val > 0 and not np.isnan(p_val)) else 1.0
                        else:
                            rr = p_val / p_oth
                        delta_abs = abs((p_val if not np.isnan(p_val) else 0.0) -
                                        (p_oth if not np.isnan(p_oth) else 0.0))
                    tmp.append({
                        "Category": feat,
                        "Value": r["Value"],
                        "Base_v": n, "Result_v": k,
                        "Base_others": base_oth, "Result_others": res_oth,
                        "Rate_v": p_val, "Rate_others": p_oth,
                        "EffSize_RR": rr,
                        "Delta_abs": delta_abs,
                        "p_raw": p_raw
                    })
                out = pd.DataFrame(tmp)
                if len(out) == 0:
                    continue
                mask = out["p_raw"].notna()
                out["p_adj"] = np.nan
                if mask.any():
                    out.loc[mask, "p_adj"] = bh_fdr(out.loc[mask, "p_raw"].values)
                out["Significativo_FDR"] = out["p_adj"] < alpha
                pv_rows.append(out)

        per_value_df = pd.concat(pv_rows, ignore_index=True) if len(pv_rows) else pd.DataFrame(
            columns=["Category","Value","Base_v","Result_v","Base_others","Result_others",
                     "Rate_v","Rate_others","EffSize_RR","Delta_abs","p_raw","p_adj","Significativo_FDR"]
        )
        return omnibus_df, per_value_df

    # ---------- run su 3 file ----------
    omni1, pv1 = _analyze_one(csv_path_1)
    omni2, pv2 = _analyze_one(csv_path_2)
    omni3, pv3 = _analyze_one(csv_path_3)

    # ---------- intersezione OMNIBUS ----------
    sig1 = set(omni1.loc[omni1["Omnibus_significativo_FDR"] == True, "Category"])
    sig2 = set(omni2.loc[omni2["Omnibus_significativo_FDR"] == True, "Category"])
    sig3 = set(omni3.loc[omni3["Omnibus_significativo_FDR"] == True, "Category"])
    common_omni = sorted(sig1 & sig2 & sig3)

    def _fisher_p(p_list):
        """Combina p-value (ignorando NaN) con metodo di Fisher."""
        arr = np.array([p for p in p_list if np.isfinite(p) and p > 0], dtype=float)
        if len(arr) == 0:
            return np.nan
        X = -2.0 * np.log(arr).sum()
        df = 2 * len(arr)
        return float(1.0 - chi2.cdf(X, df))

    omni_common_rows = []
    for cat in common_omni:
        r1 = omni1.loc[omni1["Category"] == cat].iloc[0]
        r2 = omni2.loc[omni2["Category"] == cat].iloc[0]
        r3 = omni3.loc[omni3["Category"] == cat].iloc[0]
        N_sum = int(r1["N_tot"] + r2["N_tot"] + r3["N_tot"])
        # Cramér’s V: media pesata su N_tot (euristica pratica)
        import numpy as np
        Vs = np.array([r1["CramersV"], r2["CramersV"], r3["CramersV"]], dtype=float)
        Ns = np.array([r1["N_tot"],   r2["N_tot"],   r3["N_tot"]], dtype=float)
        with np.errstate(invalid='ignore'):
            V_w = float(np.nansum(Vs * Ns) / np.nansum(Ns)) if np.nansum(Ns) > 0 else np.nan
        p_fisher = _fisher_p([r1["p_omnibus_raw"], r2["p_omnibus_raw"], r3["p_omnibus_raw"]])
        omni_common_rows.append({
            "Category": cat,
            "N_tot_pooled": N_sum,
            "CramersV_weighted": V_w,
            "p_combined_Fisher": p_fisher,
            "p_file1": float(r1["p_omnibus_raw"]),
            "p_file2": float(r2["p_omnibus_raw"]),
            "p_file3": float(r3["p_omnibus_raw"]),
        })
    omnibus_common_df = pd.DataFrame(omni_common_rows).sort_values(
        ["p_combined_Fisher","CramersV_weighted"], ascending=[True, False]
    ) if len(omni_common_rows) else pd.DataFrame(
        columns=["Category","N_tot_pooled","CramersV_weighted","p_combined_Fisher","p_file1","p_file2","p_file3"]
    )

    # ---------- intersezione PER-VALORE ----------
    # tieni solo significativi per ciascun file (NB: ora provengono solo da feature con omnibus significativo)
    pv1_sig = pv1[pv1["Significativo_FDR"] == True]
    pv2_sig = pv2[pv2["Significativo_FDR"] == True]
    pv3_sig = pv3[pv3["Significativo_FDR"] == True]

    # chiave (Category, Value)
    s1 = set(map(tuple, pv1_sig[["Category","Value"]].values))
    s2 = set(map(tuple, pv2_sig[["Category","Value"]].values))
    s3 = set(map(tuple, pv3_sig[["Category","Value"]].values))
    common_pairs = sorted(s1 & s2 & s3)

    perval_common_rows = []
    import numpy as np
    for cat, val in common_pairs:
        r1 = pv1_sig[(pv1_sig["Category"]==cat) & (pv1_sig["Value"]==val)].iloc[0]
        r2 = pv2_sig[(pv2_sig["Category"]==cat) & (pv2_sig["Value"]==val)].iloc[0]
        r3 = pv3_sig[(pv3_sig["Category"]==cat) & (pv3_sig["Value"]==val)].iloc[0]

        # pooling conteggi "valore" e "resto"
        Base_v_sum = int(r1["Base_v"] + r2["Base_v"] + r3["Base_v"])
        Result_v_sum = int(r1["Result_v"] + r2["Result_v"] + r3["Result_v"])
        Base_o_sum = int(r1["Base_others"] + r2["Base_others"] + r3["Base_others"])
        Result_o_sum = int(r1["Result_others"] + r2["Result_others"] + r3["Result_others"])

        rate_v_pool = (Result_v_sum / Base_v_sum) if Base_v_sum > 0 else np.nan
        rate_o_pool = (Result_o_sum / Base_o_sum) if Base_o_sum > 0 else np.nan

        if rate_o_pool == 0:
            RR_pool = np.inf if (rate_v_pool > 0 and not np.isnan(rate_v_pool)) else 1.0
        else:
            RR_pool = rate_v_pool / rate_o_pool

        # RR media geometrica
        def _geom_mean_rr(vals):
            arr = np.array([v for v in vals if np.isfinite(v) and v > 0], dtype=float)
            if len(arr) == 0:
                return np.nan
            return float(np.exp(np.log(arr).mean()))
        RR_geom = _geom_mean_rr([r1["EffSize_RR"], r2["EffSize_RR"], r3["EffSize_RR"]])

        p_fisher = _fisher_p([r1["p_raw"], r2["p_raw"], r3["p_raw"]])

        perval_common_rows.append({
            "Category": cat,
            "Value": val,
            "Base_v_pooled": Base_v_sum, "Result_v_pooled": Result_v_sum,
            "Base_others_pooled": Base_o_sum, "Result_others_pooled": Result_o_sum,
            "Rate_v_pooled": rate_v_pool, "Rate_others_pooled": rate_o_pool,
            "RR_pooled": RR_pool,
            "RR_geom_mean": RR_geom,
            "p_combined_Fisher": p_fisher,
            "p_file1": float(r1["p_raw"]), "p_file2": float(r2["p_raw"]), "p_file3": float(r3["p_raw"]),
        })

    per_value_common_df = pd.DataFrame(perval_common_rows).sort_values(
        ["p_combined_Fisher","RR_pooled"], ascending=[True, False]
    ) if len(perval_common_rows) else pd.DataFrame(
        columns=["Category","Value","Base_v_pooled","Result_v_pooled",
                 "Base_others_pooled","Result_others_pooled","Rate_v_pooled","Rate_others_pooled",
                 "RR_pooled","RR_geom_mean","p_combined_Fisher","p_file1","p_file2","p_file3"]
    )

    # ---------- piccolo report ----------
    lines = []
    lines.append("=== Intersezione COMUNE (3 CSV) — OMNIBUS ===")
    if len(omnibus_common_df) == 0:
        lines.append("Nessuna feature significativa in comune ai 3 file (dopo FDR individuale).")
    else:
        for _, r in omnibus_common_df.iterrows():
            lines.append(f"  - {r['Category']}: p_Fisher={r['p_combined_Fisher']:.4g}, "
                         f"V_w={r['CramersV_weighted']:.3f}, N_pooled={int(r['N_tot_pooled'])}")

    lines.append("\n=== Intersezione COMUNE (3 CSV) — PER-VALORE ===")
    if len(per_value_common_df) == 0:
        lines.append("Nessun (Category, Value) significativo in comune ai 3 file (dopo FDR individuale).")
    else:
        for _, r in per_value_common_df.head(50).iterrows():  # evita output eccessivo
            rr_str = "∞" if np.isinf(r["RR_pooled"]) else f"{r['RR_pooled']:.3f}"
            lines.append(f"  - {r['Category']} :: {r['Value']}: p_Fisher={r['p_combined_Fisher']:.4g}, "
                         f"RR_pooled={rr_str}, tasso={r['Rate_v_pooled']:.4f} vs resto={r['Rate_others_pooled']:.4f} "
                         f"(Base={int(r['Base_v_pooled'])}/{int(r['Base_others_pooled'])})")
        if len(per_value_common_df) > 50:
            lines.append(f"... ({len(per_value_common_df)-50} righe ulteriori non mostrate)")

    print("\n".join(lines))

    # ---------- ritorno strutturato ----------
    return {
        "omnibus_common": omnibus_common_df.reset_index(drop=True),
        "per_value_common": per_value_common_df.reset_index(drop=True),
        "details": {
            "single_runs": [
                {"omnibus": omni1, "per_value": pv1},
                {"omnibus": omni2, "per_value": pv2},
                {"omnibus": omni3, "per_value": pv3},
            ]
        }
    }


def combined_feature_statistical_analysis_merged(
    csv_path_1,
    csv_path_2,
    csv_path_3,
    alpha=0.05,
    mostra_non_significativi_vicini=False,
    k_vicini=5,
    min_events=0,
):
    """
    Legge tre CSV (stessa struttura: Combination, Base, Result) e produce:
      1) OMNIBUS: 'SIGNIFICATIVE' solo se tutti e 3 i file hanno omnibus significativo (p < alpha).
         In tal caso calcola anche:
           - V_combinato (media pesata dei Cramér's V, pesi = N tot per-file)
           - p_omnibus_combinato (metodo di Fisher)
      2) ANALISI PER-COMBINAZIONE: individua le combinazioni significative (FDR) comuni ai 3 file.
         Per ciascuna combinazione comune:
           - Ritorna i riassunti per-file
           - Calcola medie pesate dei tassi (pesi = Base)
           - Esegue pooling dei conteggi (somme) e rifà Barnard sulla 2×2 aggregata.

    Ritorna un dizionario con:
      {
        'omnibus_all_significant': bool,
        'omnibus_details': {
            'per_file': [
                {'file': ..., 'p_omnibus': ..., 'cramers_V': ..., 'N_tot': ...}, x3
            ],
            'combined': {
                'fisher_pvalue': ...,
                'V_weighted': ...,
                'alpha': ...
            }  # presente solo se omnibus_all_significant True
        },
        'common_significant': pandas.DataFrame  # tabella con metriche per combinazioni comuni
      }

    Note:
      - richiede SciPy con barnard_exact disponibile.
      - usa FDR (Benjamini–Hochberg) tra combinazioni per ogni file, come la funzione originale.
    """
    import pandas as pd
    import numpy as np

    # ---------- util ----------
    def bh_fdr(pvals):
        p = np.asarray(pvals, dtype=float)
        n = len(p)
        if n == 0:
            return np.array([])
        order = np.argsort(p)
        ranked = p[order]
        adj = np.empty(n)
        prev = 1.0
        for i in range(n - 1, -1, -1):
            adj[i] = min(prev, ranked[i] * n / (i + 1))
            prev = adj[i]
        out = np.empty(n); out[order] = adj
        return out

    try:
        from scipy.stats import barnard_exact as _barnard_exact  # type: ignore
        from scipy.stats import chi2
    except Exception as e:
        raise ImportError(
            "SciPy con 'barnard_exact' è richiesto. Installa/aggiorna SciPy (>=1.9)."
        ) from e

    # per Fisher
    def fisher_method(pvals):
        pvals = [p for p in pvals if np.isfinite(p) and p > 0]
        if len(pvals) == 0:
            return np.nan
        X = -2.0 * np.sum(np.log(pvals))
        df = 2 * len(pvals)
        return float(1 - chi2.cdf(X, df))

    # Barnard helper
    ALT = "two-sided"
    def barnard_p(k1, n1, k2, n2):
        if n1 <= 0 or n2 <= 0 or k1 < 0 or k2 < 0 or k1 > n1 or k2 > n2:
            return np.nan
        import numpy as _np
        table = _np.array([[k1, n1 - k1],
                           [k2, n2 - k2]], dtype=int)
        res = _barnard_exact(table, alternative=ALT)
        try:
            return float(res.pvalue)
        except AttributeError:
            _, p = res
            return float(p)

    # Omnibus χ² 2×K con p permutazionale (come l'originale)
    _B_PERM = 5000
    rng = np.random.default_rng(None)

    def _chi2_stat_from_counts(successes, bases, K=None):
        successes = successes.astype(float)
        bases = bases.astype(float)
        N = bases.sum()
        if N <= 0:
            return np.nan, np.nan, (np.nan, np.nan)
        if K is None:
            K = successes.sum()
        p = K / N
        exp_s = bases * p
        exp_f = bases * (1 - p)
        with np.errstate(divide='ignore', invalid='ignore'):
            chi_s = (successes - exp_s) ** 2 / exp_s
            chi_f = ((bases - successes) - exp_f) ** 2 / exp_f
            stat = np.nansum(chi_s) + np.nansum(chi_f)
        dof = (2 - 1) * (len(bases) - 1)
        exp_min_s = float(exp_s.min()) if len(exp_s) else np.nan
        exp_min_f = float(exp_f.min()) if len(exp_f) else np.nan
        return float(stat), int(dof), (exp_min_s, exp_min_f)

    def _perm_pvalue(successes, bases, B=_B_PERM):
        bases = bases.astype(int)
        successes = successes.astype(int)
        N = int(bases.sum()); K = int(successes.sum())
        if N <= 0:
            return np.nan, np.nan, (np.nan, np.nan), np.nan

        stat_obs, dof, exp_mins = _chi2_stat_from_counts(successes, bases, K)
        if not np.isfinite(stat_obs):
            return np.nan, stat_obs, exp_mins, np.nan

        # Cramér’s V (r=2)
        c = len(bases)
        denom = N * max(1, min(2 - 1, c - 1))
        V = float(np.sqrt(stat_obs / denom)) if (denom > 0 and np.isfinite(stat_obs)) else np.nan

        # permutazioni a totali fissi
        idx_cuts = np.cumsum(bases)[:-1]
        vec = np.zeros(N, dtype=np.int8); vec[:K] = 1
        exceed = 0
        for _ in range(B):
            rng.shuffle(vec)
            parts = np.split(vec, idx_cuts)
            perm_successes = np.fromiter((p.sum() for p in parts), dtype=np.int64, count=len(parts))
            stat_perm, _, _ = _chi2_stat_from_counts(perm_successes, bases, K)
            if np.isfinite(stat_perm) and stat_perm >= stat_obs:
                exceed += 1
        pval = (exceed + 1.0) / (B + 1.0)
        return float(pval), float(stat_obs), exp_mins, V

    # Analisi per singolo CSV -> (omnibus info, df test per-combo, df sig per-combo)
    def analyze_one(csv_path):
        df = pd.read_csv(csv_path)
        needed = {"Combination", "Base", "Result"}
        if not needed.issubset(df.columns):
            raise ValueError(f"{csv_path}: mancano colonne {needed - set(df.columns)}")

        df = df.copy()
        df["Combination"] = df["Combination"].astype(str)
        df["Base"] = pd.to_numeric(df["Base"], errors="coerce").fillna(0).astype(int)
        df["Result"] = pd.to_numeric(df["Result"], errors="coerce").fillna(0).astype(int)
        df["Result"] = df[["Result", "Base"]].min(axis=1).clip(lower=0)

        agg = df.groupby("Combination", sort=False).agg(Base=("Base","sum"),
                                                        Result=("Result","sum")).reset_index()
        agg["Rate"] = np.where(agg["Base"]>0, agg["Result"]/agg["Base"], np.nan)

        bases = agg["Base"].to_numpy(dtype=int)
        succs = agg["Result"].to_numpy(dtype=int)

        if np.sum(bases) > 0 and len(bases) >= 2:
            p_omni, chi2_stat, _, V = _perm_pvalue(succs, bases, B=_B_PERM)
            dof = (2 - 1) * (len(bases) - 1)
            N_tot = int(np.sum(bases))
        else:
            p_omni = np.nan; chi2_stat = np.nan; dof = 0; N_tot = int(np.sum(bases)); V = np.nan

        omni_significant = (np.isfinite(p_omni) and (p_omni < alpha))

        # per-combinazione (Barnard + FDR)
        base_tot = int(agg["Base"].sum())
        res_tot  = int(agg["Result"].sum())

        rows = []
        for _, r in agg.iterrows():
            comb = str(r["Combination"])
            n = int(r["Base"]); k = int(r["Result"])
            if k < min_events:
                continue
            base_oth = base_tot - n
            res_oth  = res_tot - k
            p_val = (k / n) if n > 0 else np.nan
            p_oth = (res_oth / base_oth) if base_oth > 0 else np.nan
            if n == 0 or base_oth == 0:
                p_raw = np.nan; rr = np.nan; delta = np.nan
            else:
                p_raw = barnard_p(k, n, res_oth, base_oth)
                rr = (np.inf if (p_oth == 0 and p_val > 0)
                      else (p_val / p_oth if p_oth > 0 else 1.0))
                delta = abs((p_val if not np.isnan(p_val) else 0.0) -
                            (p_oth if not np.isnan(p_oth) else 0.0))
            rows.append({
                "Combination": comb,
                "Base_v": n, "Result_v": k,
                "Rate_v": p_val, "Rate_others": p_oth,
                "EffSize_RR": rr,
                "Delta_abs": delta,
                "p_raw": p_raw,
                "Base_tot": base_tot, "Result_tot": res_tot
            })
        tests_df = pd.DataFrame(rows)
        if len(tests_df) > 0 and tests_df["p_raw"].notna().any():
            tests_df["p_adj"] = np.nan
            mask = tests_df["p_raw"].notna()
            tests_df.loc[mask, "p_adj"] = bh_fdr(tests_df.loc[mask, "p_raw"].values)
            tests_df["Significativo_FDR"] = tests_df["p_adj"] < alpha
            sig_df = tests_df[tests_df["Significativo_FDR"] == True] \
                        .sort_values(["p_adj", "EffSize_RR"], ascending=[True, False]).copy()
        else:
            tests_df = pd.DataFrame(columns=[
                "Combination","Base_v","Result_v","Rate_v","Rate_others",
                "EffSize_RR","Delta_abs","p_raw","p_adj","Significativo_FDR",
                "Base_tot","Result_tot"
            ])
            sig_df = tests_df.iloc[0:0].copy()

        return {
            "file": csv_path,
            "omnibus_significant": bool(omni_significant),
            "p_omnibus": p_omni,
            "cramers_V": V,
            "N_tot": N_tot,
            "tests_df": tests_df,
            "sig_df": sig_df
        }

    # ---------- esecuzione per i 3 file ----------
    res1 = analyze_one(csv_path_1)
    res2 = analyze_one(csv_path_2)
    res3 = analyze_one(csv_path_3)

    # ---------- OMNIBUS "tutti e 3" ----------
    all_sig = res1["omnibus_significant"] and res2["omnibus_significant"] and res3["omnibus_significant"]

    omnibus_details = {
        "per_file": [
            {"file": res1["file"], "p_omnibus": res1["p_omnibus"], "cramers_V": res1["cramers_V"], "N_tot": res1["N_tot"]},
            {"file": res2["file"], "p_omnibus": res2["p_omnibus"], "cramers_V": res2["cramers_V"], "N_tot": res2["N_tot"]},
            {"file": res3["file"], "p_omnibus": res3["p_omnibus"], "cramers_V": res3["cramers_V"], "N_tot": res3["N_tot"]},
        ]
    }

    if all_sig:
        # media pesata di V (pesi=N_tot)
        V_vals = np.array([res1["cramers_V"], res2["cramers_V"], res3["cramers_V"]], dtype=float)
        N_vals = np.array([res1["N_tot"],     res2["N_tot"],     res3["N_tot"]],     dtype=float)
        mask = np.isfinite(V_vals) & (N_vals > 0)
        V_weighted = float(np.average(V_vals[mask], weights=N_vals[mask])) if mask.any() else np.nan
        fisher_p = fisher_method([res1["p_omnibus"], res2["p_omnibus"], res3["p_omnibus"]])
        omnibus_details["combined"] = {
            "fisher_pvalue": fisher_p,
            "V_weighted": V_weighted,
            "alpha": alpha
        }

    # ---------- COMBINAZIONI SIGNIFICATIVE COMUNI ----------
    set1 = set(res1["sig_df"]["Combination"])
    set2 = set(res2["sig_df"]["Combination"])
    set3 = set(res3["sig_df"]["Combination"])
    comuni = sorted(list(set1 & set2 & set3))

    rows_common = []
    if len(comuni) > 0:
        # Prepara lookup per conteggi e tassi
        def row_of(df, comb):
            r = df[df["Combination"] == comb]
            return r.iloc[0].to_dict() if len(r) else None

        for comb in comuni:
            r1 = row_of(res1["tests_df"], comb)
            r2 = row_of(res2["tests_df"], comb)
            r3 = row_of(res3["tests_df"], comb)
            # somme per pooled
            n_v = sum([r["Base_v"]  for r in (r1,r2,r3)])
            k_v = sum([r["Result_v"] for r in (r1,r2,r3)])
            base_tot = sum([r["Base_tot"] for r in (r1,r2,r3)])
            res_tot  = sum([r["Result_tot"] for r in (r1,r2,r3)])
            base_oth = base_tot - n_v
            res_oth  = res_tot  - k_v

            # tassi pooled
            rate_v_pooled = (k_v / n_v) if n_v > 0 else np.nan
            rate_o_pooled = (res_oth / base_oth) if base_oth > 0 else np.nan
            rr_pooled = (np.inf if (rate_o_pooled == 0 and rate_v_pooled > 0)
                         else (rate_v_pooled / rate_o_pooled if rate_o_pooled > 0 else 1.0))
            delta_pooled = abs((rate_v_pooled if np.isfinite(rate_v_pooled) else 0.0) -
                               (rate_o_pooled if np.isfinite(rate_o_pooled) else 0.0))
            p_barnard_pooled = barnard_p(k_v, n_v, res_oth, base_oth)

            # medie pesate dei tassi (pesi = Base)
            # (equivalgono ai tassi pooled, ma le esplicitiamo come "media pesata")
            weights_v = np.array([r1["Base_v"], r2["Base_v"], r3["Base_v"]], dtype=float)
            rates_v = np.array([r1["Rate_v"], r2["Rate_v"], r3["Rate_v"]], dtype=float)
            mask_v = np.isfinite(rates_v) & (weights_v > 0)
            rate_v_weighted = float(np.average(rates_v[mask_v], weights=weights_v[mask_v])) if mask_v.any() else np.nan

            weights_o = np.array([
                r1["Base_tot"] - r1["Base_v"],
                r2["Base_tot"] - r2["Base_v"],
                r3["Base_tot"] - r3["Base_v"],
            ], dtype=float)
            rates_o = np.array([r1["Rate_others"], r2["Rate_others"], r3["Rate_others"]], dtype=float)
            mask_o = np.isfinite(rates_o) & (weights_o > 0)
            rate_o_weighted = float(np.average(rates_o[mask_o], weights=weights_o[mask_o])) if mask_o.any() else np.nan

            rows_common.append({
                "Combination": comb,

                # per-file (comodo per audit)
                "p_adj_file1": r1["p_raw"],  # p_raw pre-FDR; la significatività era già nota via FDR per la selezione
                "p_adj_file2": r2["p_raw"],
                "p_adj_file3": r3["p_raw"],

                "Rate_v_file1": r1["Rate_v"], "Rate_o_file1": r1["Rate_others"],
                "Rate_v_file2": r2["Rate_v"], "Rate_o_file2": r2["Rate_others"],
                "Rate_v_file3": r3["Rate_v"], "Rate_o_file3": r3["Rate_others"],

                "Base_v_sum": n_v, "Result_v_sum": k_v,
                "Base_oth_sum": base_oth, "Result_oth_sum": res_oth,

                # medie pesate (pesi = Base)
                "Rate_v_weighted": rate_v_weighted,
                "Rate_others_weighted": rate_o_weighted,

                # pooled (conteggi sommati)
                "Rate_v_pooled": rate_v_pooled,
                "Rate_others_pooled": rate_o_pooled,
                "RR_pooled": rr_pooled,
                "Delta_abs_pooled": delta_pooled,
                "p_barnard_pooled": p_barnard_pooled,
            })

    common_df = (pd.DataFrame(rows_common)
                 .sort_values(["p_barnard_pooled","RR_pooled"], ascending=[True, False])
                 if len(rows_common) else pd.DataFrame(columns=[
                     "Combination","Rate_v_weighted","Rate_others_weighted",
                     "Rate_v_pooled","Rate_others_pooled","RR_pooled","Delta_abs_pooled","p_barnard_pooled"
                 ]))

    # --------- stampa breve di esito ----------
    print("=== OMNIBUS (criterio 'tutti e 3') ===")
    if all_sig:
        print(f"Conclusione OMNIBUS: **SIGNIFICATIVE** su tutti e tre i file (α={alpha}).")
        print(f"  Fisher p-combinata = {omnibus_details['combined']['fisher_pvalue']:.4g}")
        Vw = omnibus_details['combined']['V_weighted']
        print(f"  Cramér’s V medio pesato (per N) = {Vw:.3f}")
    else:
        print(f"Conclusione OMNIBUS: **NON significative** su tutti e tre i file (almeno un file con p ≥ α={alpha}).")

    print("\n=== Combinazioni significative (FDR) comuni ai 3 file ===")
    if len(common_df) == 0:
        print("Nessuna combinazione significativa comune trovata.")
    else:
        for _, r in common_df.iterrows():
            rr_str = "∞" if np.isinf(r["RR_pooled"]) else f"{r['RR_pooled']:.3f}"
            print(
                f"  - {r['Combination']}: pooled p={r['p_barnard_pooled']:.4g}, "
                f"RR_pooled={rr_str}, |Δ|_pooled={r['Delta_abs_pooled']:.4f} "
                f"(tasso_v={r['Rate_v_pooled']:.4f} vs resto={r['Rate_others_pooled']:.4f})"
            )

    return {
        "omnibus_all_significant": all_sig,
        "omnibus_details": omnibus_details,
        "common_significant": common_df
    }


def baseline_cwe_scenario_stats(csv_path, column="Prompt ID", verbose=True):
    """
    Legge un CSV, estrae il CWE-ID dalla colonna 'Prompt ID' (parte prima di '_'),
    conta le occorrenze e restituisce { "CWE ID": Counter({...}) }.

    Parametri:
        csv_path (str): percorso al file CSV.
        column (str): nome della colonna con i Prompt ID (default: 'Prompt ID').
        verbose (bool): se True stampa un riepilogo.

    Ritorna:
        dict: {"CWE ID": Counter({ 'CWE-xxx': count, ... })}
    """
    pattern = re.compile(r"^CWE-\d+$")
    invalid_entries = []
    counter = Counter()

    df = pd.read_csv(csv_path)
    if column not in df.columns:
        raise ValueError(f"La colonna '{column}' non è presente nel file.")

    values = df[column].dropna().astype(str)

    for idx, val in values.items():
        base = val.split("_", 1)[0]  # tutto prima del primo underscore
        if pattern.match(base):
            counter[base] += 1
        else:
            invalid_entries.append((idx, val))

    # ordina per numero CWE per output leggibile
    sorted_counter = Counter(dict(sorted(
        counter.items(),
        key=lambda x: int(x[0].split("-")[1])
    )))

    if verbose:
        print(f" - {column}: {len(sorted_counter)} CWE-ID unici validi")
        for cwe, count in sorted_counter.items():
            print(f"    {cwe}: {count}")
        if invalid_entries:
            print(f"\n[!] Valori non validi trovati ({len(invalid_entries)}):")
            for idx, val in invalid_entries:
                print(f"    Riga: {idx}, Valore: '{val}'")

    return {"CWE ID": sorted_counter}


def count_extracted_files(sarif_path: str | Path, filetype: str) -> int:
    """
    Conta gli URI unici dei file estratti con successo in un SARIF CodeQL,
    in base al tipo di sorgente:
      - filetype="c"    -> "cpp/diagnostics/successfully-extracted-files"
      - filetype="java" -> "java/diagnostics/successfully-extracted-files"
      - filetype="py"   -> "py/diagnostics/successfully-extracted-files"

    Cerca gli URI in:
      - runs[].invocations[].toolExecutionNotifications[]
      - runs[].results[] (fallback)
      - runs[].tool.driver.notifications[] (ulteriore fallback)

    Ritorna:
        int: numero di URI unici.
    """
    ft = (filetype or "").strip().lower()
    TARGETS = {
        "c":    "cpp/diagnostics/successfully-extracted-files",
        "java": "java/diagnostics/successfully-extracted-files",
        "py":   "py/diagnostics/successfully-extracted-files",
    }
    if ft not in TARGETS:
        raise ValueError(f"filetype non supportato: {filetype!r}. Usa 'c', 'java' o 'py'.")

    TARGET_ID = TARGETS[ft]
    sarif_path = Path(sarif_path)
    data = json.loads(sarif_path.read_text(encoding="utf-8"))

    success_uris: set[str] = set()

    def _build_art_idx_map(artifacts: list[dict]) -> dict[int, str]:
        m: dict[int, str] = {}
        for i, a in enumerate(artifacts or []):
            loc = (a.get("location") or {})
            u = loc.get("uri")
            if u:
                m[i] = u
        return m

    def _uri_from_artloc(artloc: Optional[dict], idx_map: dict[int, str]) -> Optional[str]:
        if not artloc:
            return None
        u = artloc.get("uri")
        if u:
            return u
        idx = artloc.get("index")
        if isinstance(idx, int):
            return idx_map.get(idx)
        return None

    def _collect_uris(obj: dict, idx_map: dict[int, str]) -> list[str]:
        out: list[str] = []
        for loc in (obj.get("locations", []) or []):
            phys = (loc.get("physicalLocation") or {})
            art = (phys.get("artifactLocation") or {})
            u = _uri_from_artloc(art, idx_map)
            if u:
                out.append(u)
        for rloc in (obj.get("relatedLocations", []) or []):
            phys = (rloc.get("physicalLocation") or {})
            art = (phys.get("artifactLocation") or {})
            u = _uri_from_artloc(art, idx_map)
            if u:
                out.append(u)
        return out

    for run in (data.get("runs") or []):
        artifacts = run.get("artifacts", []) or []
        idx_map = _build_art_idx_map(artifacts)

        # 1) invocations[].toolExecutionNotifications
        for inv in (run.get("invocations") or []):
            for tn in (inv.get("toolExecutionNotifications") or []):
                desc = (tn.get("descriptor") or {})
                desc_id = desc.get("id") or tn.get("id") or tn.get("name") or ""
                if desc_id == TARGET_ID:
                    for uri in _collect_uris(tn, idx_map):
                        success_uris.add(uri)

        # 2) results[] (fallback)
        for res in (run.get("results") or []):
            rid = res.get("ruleId") or (res.get("rule") or {}).get("id")
            if rid == TARGET_ID:
                for uri in _collect_uris(res, idx_map):
                    success_uris.add(uri)

        # 3) tool.driver.notifications (ulteriore fallback)
        driver_notifs = (((run.get("tool") or {}).get("driver") or {}).get("notifications") or [])
        for notif in driver_notifs:
            nid = notif.get("id") or notif.get("name") or ""
            if nid == TARGET_ID:
                for uri in _collect_uris(notif, idx_map):
                    success_uris.add(uri)

    return len(success_uris)


def count_extracted_files_merged(
    sarif_paths: Sequence[str | Path],
    filetype: str,
) -> int:
    """
    Calcola la media intera del numero di file estratti con successo su 3 report SARIF,
    in base al linguaggio indicato (c, java, py).

    Parametri:
        sarif_paths: sequenza di 3 path verso file SARIF/JSON.
        filetype:    'c', 'java' oppure 'py'.

    Ritorna:
        int: media intera (floor) dei 3 conteggi.

    Solleva:
        ValueError se non vengono passati esattamente 3 path o se il filetype non è supportato.
        FileNotFoundError / JSONDecodeError / ecc. se i file non sono leggibili/validi.
    """
    if len(sarif_paths) != 3:
        raise ValueError(f"Attesi esattamente 3 file, ricevuti {len(sarif_paths)}.")

    counts: list[int] = []
    for p in sarif_paths:
        counts.append(count_extracted_files(p, filetype))

    # media intera (floor)
    return sum(counts) // 3


def count_vulnerable_snippets(sarif_path, language, print_report=True, show_lists=False):
    """
    Estrae il numero di file 'analizzati' (citati dai risultati NON diagnostici)
    da un report SARIF di CodeQL per C/C++, Java o Python.

    Args:
        sarif_path (str|Path): percorso al file .sarif (JSON)
        language (str): uno tra "c", "cpp", "java", "py", "python"
        print_report (bool): se True, stampa un breve riepilogo
        show_lists (bool): se True, include e stampa l'elenco degli URI analizzati

    Returns:
        dict: {"analyzed_files": <int>, "analyzed_uris": [...] (se show_lists)}
    """

    # normalizza linguaggio
    lang = (language or "").strip().lower()
    if lang in ("c", "cpp", "c++"):
        prefix = "cpp"
    elif lang in ("java",):
        prefix = "java"
    elif lang in ("py", "python"):
        prefix = "py"
    else:
        # fallback prudente: nessun prefisso → nessuna esclusione specifica
        prefix = None

    # set di regole diagnostiche da ESCLUDERE dai "risultati veri"
    # (corrispondono a quelle che hai già gestito nelle funzioni per-singolo-linguaggio)
    base_diag = {
        "baseline/expected-extracted-files",
        "diagnostics/successfully-extracted-files",
        "diagnostics/extraction-warnings",
        "diagnostics/extraction-errors",
        "diagnostics/failed-extractor-invocations",
        "diagnostic/database-quality",
        "diagnostics/syntax-error",
    }

    def _is_diagnostic(rule_id: str) -> bool:
        """Ritorna True se rule_id è una diagnostica da escludere."""
        if not rule_id:
            return False
        # match esatto con prefisso lingua (es. "cpp/diagnostics/…")
        if prefix:
            for tail in base_diag:
                if rule_id == f"{prefix}/{tail}":
                    return True
        # alcune pipeline possono già riportare il rule_id completo oppure generico: prova anche match 'termina-con'
        for tail in base_diag:
            if rule_id.endswith("/" + tail) or rule_id.endswith(tail):
                return True
        return False

    sarif_path = Path(sarif_path)
    data = json.loads(sarif_path.read_text(encoding="utf-8"))

    analyzed_uris = set()

    runs = data.get("runs", []) or []
    for run in runs:
        # mappa artifacts index -> uri
        artifacts = run.get("artifacts", []) or []
        art_idx_to_uri = {}
        for i, a in enumerate(artifacts):
            loc = (a.get("location") or {})
            u = loc.get("uri")
            if u:
                art_idx_to_uri[i] = u

        def _uri_from_artloc(artloc):
            if not artloc:
                return None
            u = artloc.get("uri")
            if u:
                return u
            idx = artloc.get("index")
            if isinstance(idx, int):
                return art_idx_to_uri.get(idx)
            return None

        def _collect_uris_from_obj(obj):
            """Estrae eventuali URI da locations e relatedLocations."""
            out = []
            for loc in (obj.get("locations", []) or []):
                phys = (loc.get("physicalLocation") or {})
                art = (phys.get("artifactLocation") or {})
                uri = _uri_from_artloc(art)
                if uri:
                    out.append(uri)
            for rloc in (obj.get("relatedLocations", []) or []):
                phys = (rloc.get("physicalLocation") or {})
                art = (phys.get("artifactLocation") or {})
                uri = _uri_from_artloc(art)
                if uri:
                    out.append(uri)
            return out

        # 1) Risultati veri: prendi tutti i results con ruleId NON diagnostico
        for res in run.get("results", []) or []:
            rid = res.get("ruleId") or (res.get("rule") or {}).get("id") or ""
            if _is_diagnostic(rid):
                continue
            for uri in _collect_uris_from_obj(res):
                analyzed_uris.add(uri)

        # Nota: per 'analyzed_files' bastano i results; le diagnostiche
        # appaiono spesso anche in invocations/notifications ma non vanno contate.
        # Non servono altri campi (expected/success/warnings/…), quindi li ignoriamo.

    summary = {
        "analyzed_files": len(analyzed_uris),
    }
    if show_lists:
        summary["analyzed_uris"] = sorted(analyzed_uris)

    if print_report:
        print(f"== CodeQL SARIF – {language.upper()} – analyzed_files ==")
        print(f"File citati nei risultati (non diagnostica): {summary['analyzed_files']}")
        if show_lists:
            print("\n-- Elenco file analizzati --")
            for u in summary["analyzed_uris"]:
                print(" ", u)

    return len(analyzed_uris)


def count_vulnerable_snippets_merged(sarif_path_1, sarif_path_2, sarif_path_3, language, print_report=True):
    """
    Calcola la media intera del numero di file 'analizzati' (non diagnostici)
    su tre report SARIF CodeQL relativi allo stesso linguaggio.

    Args:
        sarif_path_1, sarif_path_2, sarif_path_3 (str|Path): percorsi ai file .sarif
        language (str): uno tra "c", "cpp", "java", "py", "python"
        print_report (bool): se True, stampa un breve riepilogo

    Returns:
        int: media intera dei tre valori (floor della media aritmetica)
    """
    values = []
    for p in (sarif_path_1, sarif_path_2, sarif_path_3):
        # La tua funzione ritorna il conteggio (int). In caso di versioni che
        # restituissero un dict, gestiamo anche quel formato.
        v = count_vulnerable_snippets(p, language, print_report=False, show_lists=False)
        if isinstance(v, dict):
            v = v.get("analyzed_files", 0)
        values.append(int(v or 0))

    avg_int = sum(values) // 3

    if print_report:
        print(f"== Media intera su 3 report – {language.upper()} ==")
        print(f"Valori: {values[0]}, {values[1]}, {values[2]}  ->  media_intera = {avg_int}")

    return avg_int


def print_percentage(part, total, decimals=2):
    """
    Print the percentage of the first value (part) relative to the second (total).
    Example: print_percentage(25, 200) -> '12.50%'
    """
    try:
        part = float(part)
        total = float(total)
        if total == 0:
            print("Error: the second value (total) cannot be zero.")
            return
        perc = (part / total) * 100
        print(f"{perc:.{decimals}f}%")
    except (TypeError, ValueError):
        print("Error: please provide numeric values (int or float).")


def divide_and_print(numerator, denominator):
    """
    Print the result of dividing `numerator` by `denominator`.

    Args:
        numerator (float or int): The value to be divided.
        denominator (float or int): The value to divide by.

    Prints:
        The division result.

    Handles:
        ZeroDivisionError: Prints an informative message if denominator is zero.
        TypeError/ValueError: Prints a message if inputs aren't numbers.
    """
    try:
        result = float(numerator) / float(denominator)
        print(result)
    except ZeroDivisionError:
        print("Error: cannot divide by zero.")
    except (TypeError, ValueError):
        print("Error: both inputs must be numeric.")


def cwe_scenario_detection_match_merged(
    csv_path_1,
    csv_path_2,
    csv_path_3,
    delimiter=",",
    encoding="utf-8",
    base_value_for_percentage=None,
):
    """
    Legge 3 CSV con le colonne:
      - "CWE ID"        (un singolo CWE tipo 'CWE-79')
      - "Detected CWEs" (lista di CWE-ID separati da virgola)

    Fa:
      1) Calcola per ciascun CSV il numero di "corrispondenze riga" per ogni CWE:
         (una riga conta 1 se il proprio "CWE ID" è presente anche in "Detected CWEs" della stessa riga)
      2) Unisce i CWE dei tre file, calcola la media dei match per CWE su (CSV1, CSV2, CSV3)
      3) Stampa i Top 5 CWE per media match
      4) Calcola la media del numero totale di match tra i tre CSV e la stampa
      5) Se 'base_value_for_percentage' > 0, stampa: percentuale = media_totale_match / base_value_for_percentage * 100

    Parametri:
      - csv_path_1, csv_path_2, csv_path_3: path dei tre CSV
      - delimiter: delimitatore CSV (default ',')
      - encoding: encoding del file (default 'utf-8')
      - base_value_for_percentage: denominatore per la percentuale (int/float > 0)

    Ritorna:
      - pandas.DataFrame con le colonne:
          ['CWE ID', 'Match CSV1', 'Match CSV2', 'Match CSV3', 'Media match']
        (ordinato per 'Media match' decrescente)
      - media_totale_match (float)
      - percentuale (float o None)
    """
    import re
    from collections import defaultdict, Counter
    import pandas as pd
    import math

    # --- Helpers (stessi criteri della funzione originale) ---
    _re_cwe = re.compile(r"(?i)cwe[\s\-_]?(\d+)")

    def _norm_one(x):
        if x is None:
            return None
        x = str(x).strip()
        if not x:
            return None
        m = _re_cwe.search(x)
        return f"CWE-{m.group(1)}" if m else None

    def _split_detected(s):
        if s is None or (isinstance(s, float) and pd.isna(s)):
            return []
        parts = [p.strip() for p in str(s).split(",")]
        return [v for v in (_norm_one(p) for p in parts) if v is not None]

    def _per_cwe_row_matches(csv_path):
        df = pd.read_csv(csv_path, delimiter=delimiter, encoding=encoding, dtype=str)
        richieste = {"CWE ID", "Detected CWEs"}
        mancanti = richieste - set(df.columns)
        if mancanti:
            raise ValueError(f"Colonne mancanti nel CSV '{csv_path}': {', '.join(sorted(mancanti))}")

        df["_CWE"] = df["CWE ID"].apply(_norm_one)
        df["_DETS"] = df["Detected CWEs"].apply(_split_detected)

        cnt_row_matches = defaultdict(int)
        for cwe, dets in zip(df["_CWE"], df["_DETS"]):
            if cwe is not None and cwe in dets:
                cnt_row_matches[cwe] += 1

        total_matches = sum(cnt_row_matches.values())
        return Counter(cnt_row_matches), int(total_matches)

    # --- Calcolo per i tre CSV ---
    cnt1, tot1 = _per_cwe_row_matches(csv_path_1)
    cnt2, tot2 = _per_cwe_row_matches(csv_path_2)
    cnt3, tot3 = _per_cwe_row_matches(csv_path_3)

    # Unione chiavi CWE
    all_cwes = sorted(
        set(cnt1.keys()) | set(cnt2.keys()) | set(cnt3.keys()),
        key=lambda s: (int(_re_cwe.search(s).group(1)) if _re_cwe.search(s) else math.inf, s),
    )

    # Costruzione DataFrame con match per CSV e media
    import pandas as pd
    rows = []
    for cwe in all_cwes:
        m1 = cnt1.get(cwe, 0)
        m2 = cnt2.get(cwe, 0)
        m3 = cnt3.get(cwe, 0)
        media = (m1 + m2 + m3) / 3.0
        rows.append({
            "CWE ID": cwe,
            "Match CSV1": m1,
            "Match CSV2": m2,
            "Match CSV3": m3,
            "Media match": media,
        })
    out = pd.DataFrame(rows, columns=["CWE ID", "Match CSV1", "Match CSV2", "Match CSV3", "Media match"])
    out.sort_values(by="Media match", ascending=False, inplace=True, ignore_index=True)

    # --- Stampa richieste ---
    if out.empty:
        print("Nessun CWE con match trovato nei tre CSV.")
        media_totale_match = 0.0
        percentuale = None
        return out, media_totale_match, percentuale

    # Top 5 per media dei match
    top5 = out.head(5)
    print("Top 5 CWE per media dei match cross-CSV:")
    # stampa compatta
    print(top5.to_string(index=False))

    # Media del totale match tra i tre CSV
    media_totale_match = (tot1 + tot2 + tot3) / 3.0
    print(f"\nMedia del totale match (su 3 CSV): {media_totale_match:.2f}  "
          f"(CSV1={tot1}, CSV2={tot2}, CSV3={tot3})")

    # Percentuale opzionale
    percentuale = None
    if base_value_for_percentage is not None:
        try:
            denom = float(base_value_for_percentage)
            if denom > 0:
                percentuale = (media_totale_match / denom) * 100.0
                print(f"Percentuale (media_totale_match / {denom:g}): {percentuale:.2f}%")
            else:
                print("Percentuale non calcolata: 'base_value_for_percentage' deve essere > 0.")
        except (TypeError, ValueError):
            print("Percentuale non calcolata: 'base_value_for_percentage' non è numerico.")

    return out, media_totale_match, percentuale


##################################################################################################################


model_name = "qwen"

language = "Python"
language_identifier = "py"

prompt_dataset = 'LLMSecEvalDataset.csv'
sample_baseline_csv_1 = 'samples/baseline_sample_1.csv'
sample_baseline_csv_2 = 'samples/baseline_sample_2.csv'
sample_baseline_csv_3 = 'samples/baseline_sample_3.csv'
sample_permutations_folder_1 = 'samples/permutations_sample_1'
sample_permutations_folder_2 = 'samples/permutations_sample_2'
sample_permutations_folder_3 = 'samples/permutations_sample_3'


baseline_json_1 = f'samples_results/sample_1/{model_name}/json/results_{language_identifier}_baseline.sarif.json'
baseline_json_2 = f'samples_results/sample_2/{model_name}/json/results_{language_identifier}_baseline.sarif.json'
baseline_json_3 = f'samples_results/sample_3/{model_name}/json/results_{language_identifier}_baseline.sarif.json'

result_json_1 = f'samples_results/sample_1/{model_name}/json/results_{language_identifier}.sarif.json'
result_json_2 = f'samples_results/sample_2/{model_name}/json/results_{language_identifier}.sarif.json'
result_json_3 = f'samples_results/sample_3/{model_name}/json/results_{language_identifier}.sarif.json'



results_raw_1 = f'samples_results/sample_1/{model_name}/permutations/results_{language_identifier}.csv'
results_raw_2 = f'samples_results/sample_2/{model_name}/permutations/results_{language_identifier}.csv'
results_raw_3 = f'samples_results/sample_3/{model_name}/permutations/results_{language_identifier}.csv'

results_1 = f'samples_results/sample_1/{model_name}/permutations/results_{language_identifier}_complete.csv'
results_2 = f'samples_results/sample_2/{model_name}/permutations/results_{language_identifier}_complete.csv'
results_3 = f'samples_results/sample_3/{model_name}/permutations/results_{language_identifier}_complete.csv'


results_baseline_raw_1 = f'samples_results/sample_1/{model_name}/baseline/results_{language_identifier}_baseline.csv'
results_baseline_raw_2 = f'samples_results/sample_2/{model_name}/baseline/results_{language_identifier}_baseline.csv'
results_baseline_raw_3 = f'samples_results/sample_3/{model_name}/baseline/results_{language_identifier}_baseline.csv'

results_baseline_1 = f'samples_results/sample_1/{model_name}/baseline/results_{language_identifier}_baseline_complete.csv'
results_baseline_2 = f'samples_results/sample_2/{model_name}/baseline/results_{language_identifier}_baseline_complete.csv'
results_baseline_3 = f'samples_results/sample_3/{model_name}/baseline/results_{language_identifier}_baseline_complete.csv'


comparison_single_metrics_1 = f'samples_results/sample_1/{model_name}/comparison/single_metrics_comparison_{language_identifier}.csv'
comparison_single_metrics_2 = f'samples_results/sample_2/{model_name}/comparison/single_metrics_comparison_{language_identifier}.csv'
comparison_single_metrics_3 = f'samples_results/sample_3/{model_name}/comparison/single_metrics_comparison_{language_identifier}.csv'
comparison_single_metrics_merged = f'samples_results/merged/{model_name}/comparison/single_metrics_comparison_{language_identifier}.csv'


comparison_combined_metrics_1 = f'samples_results/sample_1/{model_name}/comparison/combined_metrics_comparison_{language_identifier}.csv'
comparison_combined_metrics_2 = f'samples_results/sample_2/{model_name}/comparison/combined_metrics_comparison_{language_identifier}.csv'
comparison_combined_metrics_3 = f'samples_results/sample_3/{model_name}/comparison/combined_metrics_comparison_{language_identifier}.csv'
comparison_combined_metrics_merged = f'samples_results/merged/{model_name}/comparison/combined_metrics_comparison_{language_identifier}.csv'


comparison_baseline_cwes_1 = f'samples_results/sample_1/{model_name}/comparison/baseline_cwes_comparison_{language_identifier}.csv'
comparison_baseline_cwes_2 = f'samples_results/sample_2/{model_name}/comparison/baseline_cwes_comparison_{language_identifier}.csv'
comparison_baseline_cwes_3 = f'samples_results/sample_3/{model_name}/comparison/baseline_cwes_comparison_{language_identifier}.csv'
comparison_baseline_cwes_merged = f'samples_results/merged/{model_name}/comparison/baseline_cwes_comparison_{language_identifier}.csv'


comparison_permutations_cwes_1 = f'samples_results/sample_1/{model_name}/comparison/permutations_cwes_comparison_{language_identifier}.csv'
comparison_permutations_cwes_2 = f'samples_results/sample_2/{model_name}/comparison/permutations_cwes_comparison_{language_identifier}.csv'
comparison_permutations_cwes_3 = f'samples_results/sample_3/{model_name}/comparison/permutations_cwes_comparison_{language_identifier}.csv'
comparison_permutations_cwes_merged = f'samples_results/merged/{model_name}/comparison/permutations_cwes_comparison_{language_identifier}.csv'





class BaselineCsvBuilder:
    def __init__(self):
        shutil.copy(results_baseline_raw_1, results_baseline_1)
        shutil.copy(results_baseline_raw_2, results_baseline_2)
        shutil.copy(results_baseline_raw_3, results_baseline_3)

        add_labels(results_baseline_1)
        add_labels(results_baseline_2)
        add_labels(results_baseline_3)

        add_prompt_id(results_baseline_1, prompt_dataset, "Baseline")
        add_prompt_id(results_baseline_2, prompt_dataset, "Baseline")
        add_prompt_id(results_baseline_3, prompt_dataset, "Baseline")

        add_cwe_id(results_baseline_1, "Prompt ID")
        add_cwe_id(results_baseline_2, "Prompt ID")
        add_cwe_id(results_baseline_3, "Prompt ID")

        add_prompt_info(results_baseline_1, prompt_dataset)
        add_prompt_info(results_baseline_2, prompt_dataset)
        add_prompt_info(results_baseline_3, prompt_dataset)

        add_detected_cwes(baseline_json_1, results_baseline_1)
        add_detected_cwes(baseline_json_2, results_baseline_2)
        add_detected_cwes(baseline_json_3, results_baseline_3)

        #check_and_remove_duplicates(results_baseline, remove_duplicates=False)


class PermutationCsvsBuilder:
    def __init__(self):
        enhance_permutations_csvs(sample_permutations_folder_1, sample_baseline_csv_1)
        enhance_permutations_csvs(sample_permutations_folder_2, sample_baseline_csv_2)
        enhance_permutations_csvs(sample_permutations_folder_3, sample_baseline_csv_3)


class ResultsCsvBuilder:
    def __init__(self):
        shutil.copy(results_raw_1, results_1)
        shutil.copy(results_raw_2, results_2)
        shutil.copy(results_raw_3, results_3)

        add_labels(results_1)
        add_labels(results_2)
        add_labels(results_3)

        add_prompt_id(results_1, prompt_dataset, "Results")
        add_prompt_id(results_2, prompt_dataset, "Results")
        add_prompt_id(results_3, prompt_dataset, "Results")

        add_cwe_id(results_1, "Prompt ID")
        add_cwe_id(results_2, "Prompt ID")
        add_cwe_id(results_3, "Prompt ID")

        add_slicing_info(results_1, sample_permutations_folder_1, language)
        add_slicing_info(results_2, sample_permutations_folder_2, language)
        add_slicing_info(results_3, sample_permutations_folder_3, language)

        add_detected_cwes(result_json_1, results_1)
        add_detected_cwes(result_json_2, results_2)
        add_detected_cwes(result_json_3, results_3)
        #check_and_remove_duplicates(results, remove_duplicates=False)


class BaselineStats:
    def __init__(self):
        print("***BASELINE STATS***\n")
        #print("Baseline Covered CWEs Security Scenarios:")
        #covered_cwe_types_stats(sample_baseline_csv_1, "Prompt ID")
        #covered_cwe_types_stats(sample_baseline_csv_2, "Prompt ID")
        #covered_cwe_types_stats(sample_baseline_csv_3, "Prompt ID")
        #print("\n---------------------------------------")
        #print("\nBaseline Vulnerable Security Scenarios:")
        #cwe_stats(results_baseline_1, "CWE ID", verbose=True)
        #cwe_stats(results_baseline_2, "CWE ID", verbose=True)
        #cwe_stats(results_baseline_3, "CWE ID", verbose=True)

        vulnerable_snippets = count_vulnerable_snippets_merged(baseline_json_1, baseline_json_2, baseline_json_3, language_identifier, print_report=False)
        extracted_snippets=count_extracted_files_merged([baseline_json_1, baseline_json_2, baseline_json_3], language_identifier)

        print("\nBaseline Vulnerable Snippets:")
        #compute_vulnerable_snippets(results_baseline_1, total_snippets=109)
        #compute_vulnerable_snippets(results_baseline_2, total_snippets=109)
        #compute_vulnerable_snippets(results_baseline_3, total_snippets=109)
        print(vulnerable_snippets)
        print_percentage(vulnerable_snippets, extracted_snippets)
        compute_vulnerable_snippets_merged([results_baseline_1, results_baseline_2, results_baseline_3], total_snippets=extracted_snippets)
        print("\nBaseline Detected CWEs:")
        #collect_detected_cwes(results_baseline_1, n_snippets=109)
        #collect_detected_cwes(results_baseline_2, n_snippets=109)
        #collect_detected_cwes(results_baseline_3, n_snippets=109)
        print(collect_detected_cwes_merged(results_baseline_1, results_baseline_2, results_baseline_3))
        divide_and_print(collect_detected_cwes_merged(results_baseline_1, results_baseline_2, results_baseline_3, silent=True), extracted_snippets)
        print("\nBaseline CWE Security Scenarios - Detected CWEs - Matching Cases Overview:")
        #check_cwe_match(results_baseline_1, sample_permutations_folder_1)
        #check_cwe_match(results_baseline_2, sample_permutations_folder_2)
        #check_cwe_match(results_baseline_3, sample_permutations_folder_3)
        #check_cwe_match_merged(results_baseline_1, results_baseline_2, results_baseline_3)
        cwe_scenario_detection_match_merged(results_baseline_1, results_baseline_2, results_baseline_3, base_value_for_percentage=extracted_snippets)
        print("\n----------------------------------------------------------------\n")


class PermutationsStats:
    def __init__(self):
        print("***PERMUTATIONS STATS***\n")
        print("Total permutations over baseline:")
        total_permutations_over_baseline(sample_permutations_folder_1)
        total_permutations_over_baseline(sample_permutations_folder_2)
        total_permutations_over_baseline(sample_permutations_folder_3)
        print("\n---------------------------------------\n")

        permutations_single_metrics_stats(sample_permutations_folder_1, verbose=True)
        permutations_single_metrics_stats(sample_permutations_folder_2, verbose=True)
        permutations_single_metrics_stats(sample_permutations_folder_3, verbose=True)
        print("\n---------------------------------------\n")

        permutations_combined_metrics_stats(sample_permutations_folder_1, verbose=True)
        permutations_combined_metrics_stats(sample_permutations_folder_2, verbose=True)
        permutations_combined_metrics_stats(sample_permutations_folder_3, verbose=True)
        print("\n---------------------------------------\n")

        print("\nPermutation CWEs Stats:")
        permutations_cwe_stats(sample_permutations_folder_1, "CWE ID", verbose=True)
        permutations_cwe_stats(sample_permutations_folder_2, "CWE ID", verbose=True)
        permutations_cwe_stats(sample_permutations_folder_3, "CWE ID", verbose=True)

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
        #single_metrics_stats(results_1, verbose=True)
        #single_metrics_stats(results_2, verbose=True)
        #single_metrics_stats(results_3, verbose=True)
        #print("\n---------------------------------------\n")

        #print("\nCombined Metrics Stats:")
        #combined_metrics_stats(results_1, verbose=True)
        #combined_metrics_stats(results_2, verbose=True)
        #combined_metrics_stats(results_3, verbose=True)
        #print("\n---------------------------------------\n")

        #print("\nVulnerable CWE Scenarios:")
        #cwe_stats(results_1, "CWE ID", verbose=True)
        #cwe_stats(results_2, "CWE ID", verbose=True)
        #cwe_stats(results_3, "CWE ID", verbose=True)
        #print("\n---------------------------------------\n")

        vulnerable_snippets = count_vulnerable_snippets_merged(result_json_1, result_json_2, result_json_3, language_identifier)
        extracted_snippets=count_extracted_files_merged([result_json_1, result_json_2, result_json_3], language_identifier)

        print("\nVulnerable Snippets:")
        #compute_vulnerable_snippets(results_1, total_snippets=353)
        #compute_vulnerable_snippets(results_2, total_snippets=353)
        #compute_vulnerable_snippets(results_3, total_snippets=353)
        print(vulnerable_snippets)
        print_percentage(vulnerable_snippets, extracted_snippets)
        #compute_vulnerable_snippets_merged([results_1, results_2, results_3], total_snippets=extracted_snippets)
        print("\n---------------------------------------\n")

        print("\nDetected CWEs:")
        #collect_detected_cwes(results_1)
        #collect_detected_cwes(results_2)
        #collect_detected_cwes(results_3)
        print(collect_detected_cwes_merged(results_1, results_2, results_3))
        divide_and_print(collect_detected_cwes_merged(results_1, results_2, results_3), extracted_snippets)
        print("\n---------------------------------------\n")

        print("\nTotal CWE Security Scenarios - Detected CWEs - Matching Cases Overview:")
        #check_cwe_match(results_1, sample_permutations_folder_1)
        #check_cwe_match(results_2, sample_permutations_folder_2)
        #check_cwe_match(results_3, sample_permutations_folder_3)
        #check_cwe_match_merged(results_1, results_2, results_3)
        cwe_scenario_detection_match_merged(results_1, results_2, results_3, base_value_for_percentage=extracted_snippets)
        print("\n----------------------------------------------------------------\n")


# Comparison between slicing features from baseline to detected vulnerabilities
class MetricsComparison:
    def __init__(self):
        print("***METRICS COMPARISON***\n")
        permutation_single_metrics_1 = permutations_single_metrics_stats(sample_permutations_folder_1, verbose=False)
        permutation_single_metrics_2 = permutations_single_metrics_stats(sample_permutations_folder_2, verbose=False)
        permutation_single_metrics_3 = permutations_single_metrics_stats(sample_permutations_folder_3, verbose=False)

        result_single_metrics_1 = single_metrics_stats(results_1, verbose=False)
        result_single_metrics_2 = single_metrics_stats(results_2, verbose=False)
        result_single_metrics_3 = single_metrics_stats(results_3, verbose=False)


        permutation_combined_metrics_1 = permutations_combined_metrics_stats(sample_permutations_folder_1, verbose=False)
        permutation_combined_metrics_2 = permutations_combined_metrics_stats(sample_permutations_folder_2, verbose=False)
        permutation_combined_metrics_3 = permutations_combined_metrics_stats(sample_permutations_folder_3, verbose=False)

        result_combined_metrics_1 = combined_metrics_stats(results_1, verbose=False)
        result_combined_metrics_2 = combined_metrics_stats(results_2, verbose=False)
        result_combined_metrics_3 = combined_metrics_stats(results_3, verbose=False)


        # These values show the frequency of syntagm types, granularity and indexes of the results based on the permutations stats
        print("\nSingle Metrics Comparison Stats:")
        compare_single_metric(permutation_single_metrics_1, result_single_metrics_1, comparison_single_metrics_1)
        compare_single_metric(permutation_single_metrics_2, result_single_metrics_2, comparison_single_metrics_2)
        compare_single_metric(permutation_single_metrics_3, result_single_metrics_3, comparison_single_metrics_3)

        print("\nCombined Metrics Comparison Stats:")
        compare_combined_metrics(permutation_combined_metrics_1, result_combined_metrics_1, comparison_combined_metrics_1)
        compare_combined_metrics(permutation_combined_metrics_2, result_combined_metrics_2, comparison_combined_metrics_2)
        compare_combined_metrics(permutation_combined_metrics_3, result_combined_metrics_3, comparison_combined_metrics_3)

        print("\nSingle Features Statistical Analysis Stats:")
        analyze_single_feature_significance(comparison_single_metrics_1)
        analyze_single_feature_significance(comparison_single_metrics_2)
        analyze_single_feature_significance(comparison_single_metrics_3)

        print("\nCombined Features Statistical Analysis Stats:")
        analyze_combined_features_significance(comparison_combined_metrics_1)
        analyze_combined_features_significance(comparison_combined_metrics_2)
        analyze_combined_features_significance(comparison_combined_metrics_3)
        print("\n----------------------------------------------------------------\n")



# Comparison between vulnerability scenarios from baseline and detected vulnerabilities
class CWEComparison:
    def __init__(self):
        print("***CWE COMPARISON***\n")
        baseline_scenarios_1 = baseline_cwe_scenario_stats(sample_baseline_csv_1, verbose=False)
        baseline_scenarios_2 = baseline_cwe_scenario_stats(sample_baseline_csv_2, verbose=False)
        baseline_scenarios_3 = baseline_cwe_scenario_stats(sample_baseline_csv_3, verbose=False)

        baseline_cwes_1 = cwe_stats(results_baseline_1, "CWE ID", verbose=False)
        baseline_cwes_2 = cwe_stats(results_baseline_2, "CWE ID", verbose=False)
        baseline_cwes_3 = cwe_stats(results_baseline_3, "CWE ID", verbose=False)

        permutations_cwes_1 = permutations_cwe_stats(sample_permutations_folder_1, "CWE ID", verbose=False)
        permutations_cwes_2 = permutations_cwe_stats(sample_permutations_folder_2, "CWE ID", verbose=False)
        permutations_cwes_3 = permutations_cwe_stats(sample_permutations_folder_3, "CWE ID", verbose=False)

        result_cwes_1 = cwe_stats(results_1, "CWE ID", verbose=False)
        result_cwes_2 = cwe_stats(results_2, "CWE ID", verbose=False)
        result_cwes_3 = cwe_stats(results_3, "CWE ID", verbose=False)


        # These values compare the security scenario that yielded vulnerabilities from the baseline to the total results
        print("\nBaseline - Results --- Metrics CWE Stats:")
        compare_cwe_counters(baseline_scenarios_1, baseline_cwes_1, comparison_baseline_cwes_1)
        compare_cwe_counters(baseline_scenarios_2, baseline_cwes_2, comparison_baseline_cwes_2)
        compare_cwe_counters(baseline_scenarios_3, baseline_cwes_3, comparison_baseline_cwes_3)

        # These values compare the total security scenario over the permutations with those that are vulnerable
        print("\nPermutations - Results --- Metrics CWE Stats:")
        compare_cwe_counters(permutations_cwes_1, result_cwes_1, comparison_permutations_cwes_1)
        compare_cwe_counters(permutations_cwes_2, result_cwes_2, comparison_permutations_cwes_2)
        compare_cwe_counters(permutations_cwes_3, result_cwes_3, comparison_permutations_cwes_3)

        #compare_detected_cwe_frequencies(collect_detected_cwes(results_baseline_1, quiet=True), collect_detected_cwes(results_1, quiet=True))
        #compare_detected_cwe_frequencies(collect_detected_cwes(results_baseline_2, quiet=True), collect_detected_cwes(results_2, quiet=True))
        #compare_detected_cwe_frequencies(collect_detected_cwes(results_baseline_3, quiet=True), collect_detected_cwes(results_3, quiet=True))
        print("\n----------------------------------------------------------------\n")


class SamplesAnalysis:
    def __init__(self):
        print("***SAMPLES ANALYSIS***\n")
        cwe_scenarios_frequency_mean(comparison_baseline_cwes_1, comparison_baseline_cwes_2, comparison_baseline_cwes_3, comparison_baseline_cwes_merged)
        cwe_scenarios_frequency_mean(comparison_permutations_cwes_1, comparison_permutations_cwes_2, comparison_permutations_cwes_3, comparison_permutations_cwes_merged)
        single_feature_frequency_mean_to_csv(comparison_single_metrics_1, comparison_single_metrics_2, comparison_single_metrics_3, comparison_single_metrics_merged)
        combined_feature_frequency_mean_to_csv(comparison_combined_metrics_1, comparison_combined_metrics_2, comparison_combined_metrics_3, comparison_combined_metrics_merged)
        print("Merged Single Features Statistical Analysis Stats:")
        single_feature_statistical_analysis_merged(comparison_single_metrics_1, comparison_single_metrics_2, comparison_single_metrics_3)
        print("Merged Combined Features Statistical Analysis Stats:")
        combined_feature_statistical_analysis_merged(comparison_combined_metrics_1, comparison_combined_metrics_2, comparison_combined_metrics_3)


BaselineCsvBuilder()
PermutationCsvsBuilder()
ResultsCsvBuilder()

BaselineStats()
ResultStats()
PermutationsStats()

MetricsComparison()
#CWEComparison()

SamplesAnalysis()
