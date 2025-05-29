import csv
import os
import re
import shutil
import pandas as pd


def label_output_csv(input_csv_path):
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


def add_identifiers(csv_path: str, dataset_csv_path: str) -> None:
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


def extract_cwe_id(csv_path, original_column):
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


def snippets_count(folder):
    count = 0
    for root, dirs, files in os.walk(folder):
        # Escludi le directory nascoste
        dirs[:] = [d for d in dirs if not d.startswith('.')]

        # Conta solo i file visibili
        for file in files:
            if not file.startswith('.'):
                file_path = os.path.join(root, file)
                if os.path.isfile(file_path):
                    count += 1
    print("Total snippets:", count)
    return count

def row_counter(csv_path):
    print("Total issues:", len(open(csv_path, encoding='utf-8').readlines()))


##################################################################################################################


prompt_dataset = 'LLMSecEvalDataset.csv'
result_py = 'results_codeql/results_py.csv'
result_py_complete = 'results_codeql/results_py_complete.csv'
snippets_folder = 'generated_code'


class Stats:
    def __init__(self):
        snippets_count(snippets_folder)
        row_counter(result_py_complete)


class ResultAnalysis:
    def __init__(self):
        shutil.copy(result_py, result_py_complete)
        label_output_csv(result_py_complete)
        check_and_remove_duplicates(result_py_complete, remove_duplicates=False)
        add_identifiers(result_py_complete, prompt_dataset)
        extract_cwe_id(result_py_complete, "Prompt ID")

Stats()
ResultAnalysis()