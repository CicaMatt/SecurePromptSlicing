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


def add_prompt_id(csv_path: str, dataset_csv_path: str, mode: str = 'Results') -> None:
    """
    Modifica il CSV iniziale aggiungendo le colonne 'Prompt ID' e 'Dataset ID'
    ottenute dal mapping tramite l'ID estratto dal campo 'Path'.

    Args:
        csv_path (str): Percorso del CSV iniziale con colonna 'Path'.
        dataset_csv_path (str): Percorso del CSV contenente 'Id' e 'Prompt ID'.
        mode: Aggiunta per la baseline o per i risultati
    """
    # Legge il CSV iniziale
    starting_df = pd.read_csv(csv_path)

    # Estrae il numero da "permutations_"
    def extract_id(path):
        if mode == 'Results':
            match = re.search(r'permutations_(\d+)', path)
            return int(match.group(1)) if match else None
        elif mode == 'Baseline':
            match = re.search(r'row_(\d+)', path)
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


def permutations_values_count_total(folder, verbose=True):
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
                if verbose:
                    print(f"Errore nella lettura di {filename}: {e}")

    if verbose:
        print(f"Totale righe lette da tutti i CSV: {total_rows}\n")

        print(f" - Type: {len(type_counter)} unique values")
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
        'Type': type_counter,
        'Granularity': granularity_counter,
        'Sentence Index': sentence_index_counter,
    }



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



def compare_cwe_counters(base_counters, result_counters):
    """
    Confronta due dizionari nel formato restituito da result_cwe_stats:
    { "CWE ID": Counter({ "CWE-XX": count, ... }) }

    Stampa la percentuale dei valori result rispetto a quelli base.
    """

    if "CWE ID" not in base_counters or "CWE ID" not in result_counters:
        print("❌ Errore: almeno uno dei dizionari non contiene la chiave 'CWE ID'")
        return

    base_counter = base_counters["CWE ID"]
    result_counter = result_counters["CWE ID"]

    print("\n--- CONFRONTO CWE (CWE ID) ---\n")

    all_keys = set(base_counter) | set(result_counter)

    for cwe in sorted(all_keys, key=lambda x: int(x.replace("CWE-", ""))):
        base_val = base_counter.get(cwe, 0)
        result_val = result_counter.get(cwe, 0)

        if base_val == 0:
            percent = "N/A"
        else:
            percent = f"{(result_val / base_val) * 100:.2f}%"

        print(f"{cwe:10}: {result_val:4} / {base_val:4} → {percent}")


def enhance_permutations_csvs(folder_path, mapping_file):
    # Carica il file di mapping
    df_mapping = pd.read_csv(mapping_file)

    # Itera su ogni riga del file di mapping
    for index, row in df_mapping.iterrows():
        nome_csv = f"syntactic_permutations_{index + 1}.csv"
        percorso_csv = os.path.join(folder_path, nome_csv)

        if not os.path.exists(percorso_csv):
            print(f"File non trovato: {percorso_csv}")
            continue

        # Carica il CSV corrispondente
        df = pd.read_csv(percorso_csv)

        # Controlla se le colonne esistono già
        colonne_da_aggiungere = {
            "ID": row.get("ID", ""),
            "Prompt ID": row.get("Prompt ID", ""),
            "CWE-ID": row.get("Prompt ID", "").split("_")[0] if "_" in row.get("Prompt ID", "") else ""
        }

        modificato = False

        for colonna, valore in colonne_da_aggiungere.items():
            if colonna not in df.columns:
                df[colonna] = valore
                modificato = True

        if modificato:
            df.to_csv(percorso_csv, index=False)
            print(f"Aggiornato: {percorso_csv}")
        else:
            print(f"Nessuna modifica necessaria: {percorso_csv}")

r"""
can be deleted
def result_cwe_stats_from_folder(folder_path, cwe_column="CWE ID", verbose=True):
    aggregate_counter = Counter()
    total_rows = 0
    files_processed = 0

    for filename in os.listdir(folder_path):
        if filename.lower().endswith(".csv"):
            file_path = os.path.join(folder_path, filename)
            try:
                df = pd.read_csv(file_path)

                if cwe_column not in df.columns:
                    if verbose:
                        print(f"⚠️  Colonna '{cwe_column}' non trovata in '{filename}' - ignorato.")
                    continue

                current_counter = Counter(df[cwe_column].dropna().astype(str))
                aggregate_counter.update(current_counter)
                total_rows += len(df)
                files_processed += 1

            except Exception as e:
                if verbose:
                    print(f"❌ Errore nella lettura di '{filename}': {e}")

    # Ordina per ID numerico (es. "CWE-502" -> 502)
    sorted_aggregate = dict(sorted(
        aggregate_counter.items(),
        key=lambda x: int(x[0].replace("CWE-", "")) if x[0].startswith("CWE-") else float('inf')
    ))

    if verbose:
        print(f"\n📁 Totale file letti: {files_processed}")
        print(f"📄 Totale righe lette: {total_rows}")
        print(f"🔢 CWE unici trovati: {len(sorted_aggregate)}\n")
        for cwe, count in sorted_aggregate.items():
            print(f"  {cwe}: {count}")

    return Counter(sorted_aggregate)
"""



##################################################################################################################


prompt_dataset = 'LLMSecEvalDataset.csv'
result_py = 'results_codeql/results_py.csv'
result_py_complete = 'results_codeql/results_py_complete.csv'
result_py_baseline = 'results_codeql/results_py_baseline.csv'
result_py_baseline_complete = 'results_codeql/results_py_baseline_complete.csv'

#result_py_complete = 'results_codeql/results_py_standardpack.csv'
#result_py_complete = 'results_codeql/results_py_custompack.csv'

snippets_folder = 'generated_code'
permutations_folder = 'permutations'


class BaselineCsvBuilder:
    def __init__(self):
        shutil.copy(result_py_baseline, result_py_baseline_complete)
        add_labels(result_py_baseline_complete)
        add_prompt_id(result_py_baseline_complete, prompt_dataset, "Baseline")
        add_cwe_id(result_py_baseline_complete, "Prompt ID")
        #check_and_remove_duplicates(result_py_baseline_complete, remove_duplicates=False)


class PermutationCsvsBuilder:
    def __init__(self):
        enhance_permutations_csvs(permutations_folder, prompt_dataset)


class ResultsCsvBuilder:
    def __init__(self):
        shutil.copy(result_py, result_py_complete)
        add_labels(result_py_complete)
        add_prompt_id(result_py_complete, prompt_dataset, "Results")
        add_cwe_id(result_py_complete, "Prompt ID")
        add_slicing_info(result_py_complete, permutations_folder)
        #check_and_remove_duplicates(result_py_complete, remove_duplicates=False)


class BaselineStats:
    def __init__(self):
        print("Baseline Covered CWEs (Security Scenarios):")
        covered_cwe_types_stats(prompt_dataset, "Prompt ID")
        print("\n---------------------------------------")
        print("\nBaseline CWEs Stats (Baseline Analysis on Default Prompts):")
        cwe_stats(result_py_baseline_complete, "CWE ID", verbose=True)


class PermutationsStats:
    def __init__(self):
        #print("Permutations Stats - All")
        #permutations_values_count_total(permutations_folder)
        #analyze_snippets(snippets_folder)
        #print("\n---------------------------------------")
        #print("\nPermutations Stats - Correct Snippets:")
        #permutations_values_count_clean(permutations_folder, snippets_folder)
        print("\nPermutation CWEs Stats:")
        permutations_cwe_stats(permutations_folder, "CWE ID", verbose=True)


class ResultStats:
    def __init__(self):
        #snippets_count(snippets_folder)
        #row_counter(result_py_complete)
        #print("\nResult Stats:")
        #result_values_count(result_py_complete)
        #print("\n---------------------------------------")
        print("\nResult CWEs Stats:")
        cwe_stats(result_py_complete, "CWE ID", verbose=True)


class BaselineComparison:
    def __init__(self):
        print("\nBaseline Comparison:")


class MetricsComparison:
    def __init__(self):
        #print("\nPermutations Metrics Stats")
        #base_metrics = permutations_values_count_clean(permutations_folder, snippets_folder, verbose=False)
        base_metrics = permutations_values_count_total(permutations_folder, verbose=False)
        #print("\n---------------------------------------")
        #print("\nResult Stats:")
        result_metrics = result_values_count(result_py_complete, verbose=False)
        #print("\n---------------------------------------")
        # These values show the frequency of syntagm types, granularity and indexes of the results based on the permutations stats
        print("\nMetrics Comparison Stats:")
        compare_metric_counters(base_metrics, result_metrics)


# Comparison of
class CWEComparison:
    def __init__(self):
        #print("\nBaseline CWEs Stats:")
        #print("\n---------------------------------------")
        baseline_cwes = cwe_stats(result_py_baseline_complete, "CWE ID", verbose=False)
        #print("\nPermutation CWEs Stats:")
        permutations_cwes = permutations_cwe_stats(permutations_folder, "CWE ID", verbose=False)
        #print("\n---------------------------------------")
        #print("\nResult CWEs Stats:")
        result_cwes = cwe_stats(result_py_complete, "CWE ID", verbose=False)
        #print("\n---------------------------------------")

        # These values show how many of the detected vulnerabilities over the baseline are present over the results
        print("\nBaseline - Results --- Metrics CWE Stats:")
        compare_cwe_counters(result_cwes, baseline_cwes)
        # These values show how security scenarios covered over the permutations yielded a vulnerability based on the results
        print("\nPermutations - Results --- Metrics CWE Stats:")
        compare_cwe_counters(permutations_cwes, result_cwes)





#BaselineCsvBuilder()
#PermutationCsvsBuilder()
#ResultsCsvBuilder()
#BaselineStats()
#PermutationsStats()
#ResultStats()
#BaselineComparison()
MetricsComparison()
#CWEComparison()