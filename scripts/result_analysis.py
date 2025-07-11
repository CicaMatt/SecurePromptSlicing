import ast
import csv
import os
import re
import shutil
import traceback
from collections import Counter
from itertools import combinations

import pandas as pd
import warnings
import matplotlib.pyplot as plt
from dask.delayed import single_key

warnings.filterwarnings("ignore", category=SyntaxWarning)


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
        print(f"Total rows processed: {total_rows}")
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


##################################################################################################################


language = "C"
language_identifier = "c"

prompt_dataset = 'LLMSecEvalDataset.csv'
permutations_folder = 'permutations'

baseline_snippets_folder = f'generated_code/baseline_code_{language_identifier}'
permutations_snippets_folder = f'generated_code/generated_code_{language_identifier}'

results_codeql_raw = f'results/permutations/results_{language_identifier}.csv'
results_codeql = f'results/permutations/results_{language_identifier}_complete.csv'
results_baseline_raw = f'results/baseline/results_{language_identifier}_baseline.csv'
results_baseline = f'results/baseline/results_{language_identifier}_baseline_complete.csv'

comparison_single_metrics = f'results/comparison/single_metrics_comparison_{language_identifier}.csv'
comparison_combined_metrics = f'results/comparison/combined_metrics_comparison_{language_identifier}.csv'
comparison_baseline_cwes = f'results/comparison/baseline_cwes_comparison_{language_identifier}.csv'
comparison_permutations_cwes = f'results/comparison/permutations_cwes_comparison_{language_identifier}.csv'


#result_py_complete = 'results/permutations/results_py_standardpack.csv'
#result_py_complete = 'results/permutations/results_py_custompack.csv'



class BaselineCsvBuilder:
    def __init__(self):
        shutil.copy(results_baseline_raw, results_baseline)
        add_labels(results_baseline)
        add_prompt_id(results_baseline, prompt_dataset, "Baseline")
        add_cwe_id(results_baseline, "Prompt ID")
        add_prompt_info(results_baseline, prompt_dataset)
        #check_and_remove_duplicates(results_baseline, remove_duplicates=False)


class PermutationCsvsBuilder:
    def __init__(self):
        enhance_permutations_csvs(permutations_folder, prompt_dataset)


class ResultsCsvBuilder:
    def __init__(self):
        shutil.copy(results_codeql_raw, results_codeql)
        add_labels(results_codeql)
        add_prompt_id(results_codeql, prompt_dataset, "Results")
        add_cwe_id(results_codeql, "Prompt ID")
        add_slicing_info(results_codeql, permutations_folder, language)
        #check_and_remove_duplicates(results, remove_duplicates=False)


class BaselineStats:
    def __init__(self):
        print("***BASELINE STATS***\n")
        print("Baseline Covered CWEs (Security Scenarios):")
        covered_cwe_types_stats(prompt_dataset, "Prompt ID")
        print("\n---------------------------------------")
        print("\nBaseline CWEs Stats (Baseline Analysis on Default Prompts):")
        cwe_stats(results_baseline, "CWE ID", verbose=True)
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
        print("Total snippets over baseline:")
        count_files_by_extension(baseline_snippets_folder, "." + language_identifier)
        print("Total snippets over permutations:")
        count_files_by_extension(permutations_snippets_folder, "." + language_identifier)
        print("\nTotal vulnerabilities/warnings found:")
        row_counter(results_codeql)
        print("\n---------------------------------------\n")

        print("\nSingle Metrics Stats:")
        single_metrics_stats(results_codeql, verbose=True)
        print("\n---------------------------------------\n")

        print("\nCombined Metrics Stats:")
        combined_metrics_stats(results_codeql, verbose=True)
        print("\n---------------------------------------\n")

        print("\nResult CWEs Stats:")
        cwe_stats(results_codeql, "CWE ID", verbose=True)
        print("\n----------------------------------------------------------------\n")


# Comparison between slicing features from baseline to detected vulnerabilities
class MetricsComparison:
    def __init__(self):
        print("***METRICS COMPARISON***\n")
        permutation_single_metrics = permutations_single_metrics_stats(permutations_folder, verbose=False)
        result_single_metrics = single_metrics_stats(results_codeql, verbose=False)

        permutation_combined_metrics = permutations_combined_metrics_stats(permutations_folder, verbose=False)
        result_combined_metrics = combined_metrics_stats(results_codeql, verbose=False)

        # These values show the frequency of syntagm types, granularity and indexes of the results based on the permutations stats
        print("\nSingle Metrics Comparison Stats:")
        compare_single_metric(permutation_single_metrics, result_single_metrics, comparison_single_metrics)

        print("\nCombined Metrics Comparison Stats:")
        compare_combined_metrics(permutation_combined_metrics, result_combined_metrics, comparison_combined_metrics)

        # Plotting data
        plot_metric_comparison(permutation_single_metrics, result_single_metrics, "Syntagm Type", "Frequency", True)
        plot_metric_comparison(permutation_single_metrics, result_single_metrics, "Granularity", "Frequency", True)
        plot_metric_comparison(permutation_single_metrics, result_single_metrics, "Sentence Index", "Frequency", True)
        print("\n----------------------------------------------------------------\n")



# Comparison between vulnerability scenarios from baseline and detected vulnerabilities
class CWEComparison:
    def __init__(self):
        print("***CWE COMPARISON***\n")
        baseline_cwes = cwe_stats(results_baseline, "CWE ID", verbose=False)
        permutations_cwes = permutations_cwe_stats(permutations_folder, "CWE ID", verbose=False)
        result_cwes = cwe_stats(results_codeql, "CWE ID", verbose=False)

        # These values compare the security scenario that yielded vulnerabilities from the baseline to the total results
        print("\nBaseline - Results --- Metrics CWE Stats:")
        compare_cwe_counters(result_cwes, baseline_cwes, comparison_baseline_cwes)
        # These values compare the total security scenario over the permutations with those that are vulnerable
        print("\nPermutations - Results --- Metrics CWE Stats:")
        compare_cwe_counters(permutations_cwes, result_cwes, comparison_permutations_cwes)

        # Plotting data
        plot_cwe_comparison(result_cwes, baseline_cwes, "Baseline", "Frequency", True)
        plot_cwe_comparison(permutations_cwes, result_cwes, "Permutations", "Frequency", True)
        print("\n----------------------------------------------------------------\n")



BaselineCsvBuilder()
PermutationCsvsBuilder()
ResultsCsvBuilder()

BaselineStats()
PermutationsStats()
ResultStats()

MetricsComparison()
CWEComparison()
