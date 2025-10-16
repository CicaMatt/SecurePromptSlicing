import csv
import json
import os
import re
import shutil
from collections import Counter
from itertools import combinations
from pathlib import Path
from typing import Dict, Set, Optional, Tuple, List

import numpy as np
import pandas as pd


def add_labels(input_csv_path):
    column_labels = [
        "Name",
        "Description",
        "Severity",
        "Message",
        "Path",
        "StartLine",
        "StartColumn",
        "EndLine",
        "EndColumn"
    ]

    if os.path.getsize(input_csv_path) == 0:
        pd.DataFrame(columns=column_labels).to_csv(input_csv_path, index=False)
    else:
        df = pd.read_csv(input_csv_path, header=None)
        df.columns = column_labels
        df.to_csv(input_csv_path, index=False)


def add_prompt_id(csv_path: str, dataset_csv_path: str, mode: str = 'Results') -> None:
    starting_df = pd.read_csv(csv_path)

    def extract_id(path):
        if mode == 'Results':
            match = re.search(r'permutations_(\d+)', path)
            return int(match.group(1)) if match else None
        elif mode == 'Baseline':
            match = re.search(r'row_(\d+)', path)
            return int(match.group(1)) if match else None

    starting_df['Permutation_ID'] = starting_df['Path'].apply(extract_id)

    starting_df['Permutation_ID'] = pd.to_numeric(starting_df['Permutation_ID'], errors='coerce')

    df_mapping = pd.read_csv(dataset_csv_path)

    df_mapping['ID'] = pd.to_numeric(df_mapping['ID'], errors='coerce')

    starting_df = starting_df.merge(
        df_mapping[['ID', 'Prompt ID']],
        left_on='Permutation_ID',
        right_on='ID',
        how='left'
    )

    starting_df.rename(columns={'ID': 'Dataset ID'}, inplace=True)

    starting_df.drop(columns=['Permutation_ID'], inplace=True)

    starting_df.to_csv(csv_path, index=False)


def add_cwe_id(csv_path, original_column):
    df = pd.read_csv(csv_path)
    if original_column not in df.columns:
        raise ValueError(f"La colonna '{original_column}' non esiste nel CSV.")
    df["CWE ID"] = df[original_column].astype(str).str.split("_").str[0]
    df.to_csv(csv_path, index=False)


def add_slicing_info(input_csv_path, lookup_dir, language):
    df = pd.read_csv(input_csv_path)

    if "Path" not in df.columns:
        raise ValueError("La colonna 'Path' non è presente nel CSV iniziale.")

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

            zero_based_index = row_number - 1

            if 0 <= zero_based_index < len(lookup_df):
                row = lookup_df.iloc[zero_based_index]

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

    df["Sliced Prompt"] = sliced_prompts
    df["Original Sentence"] = original_sentences
    df["Removed Part"] = removed_parts
    df["Sentence Index"] = sentence_indices
    df["Syntagm Type"] = syntagm_types
    df["Granularity"] = granularities
    df["Resulting Prompt"] = resulting_prompts

    df.to_csv(input_csv_path, index=False)


def add_prompt_info(csv1_path, csv2_path):
    df1 = pd.read_csv(csv1_path)
    df2 = pd.read_csv(csv2_path)

    if 'Dataset ID' not in df1.columns or 'ID' not in df2.columns or 'Manually-fixed NL Prompt' not in df2.columns:
        raise ValueError("CSV1 deve avere 'Dataset ID'; CSV2 deve avere 'ID' e 'Manually-fixed NL Prompt'.")

    id_to_prompt = dict(zip(df2['ID'], df2['Manually-fixed NL Prompt']))
    df1['Prompt'] = df1['Dataset ID'].map(id_to_prompt)
    df1.to_csv(csv1_path, index=False)


def cwe_stats(csv_path, cwe_column, verbose=True):
    try:
        df = pd.read_csv(csv_path)

        if cwe_column not in df.columns:
            raise ValueError(f"La colonna '{cwe_column}' non esiste nel CSV.")

        cwe_counts = Counter(df[cwe_column].dropna().astype(str))

        sorted_cwe_counts = dict(sorted(
            cwe_counts.items(),
            key=lambda x: int(x[0].replace("CWE-", "")) if x[0].startswith("CWE-") else float('inf')
        ))

        if verbose:
            print(f" - {cwe_column}: {len(sorted_cwe_counts)} valori unici")
            for cwe, count in sorted_cwe_counts.items():
                print(f"    {cwe}: {count}")

        return {cwe_column: Counter(sorted_cwe_counts)}

    except Exception as e:
        if verbose:
            print(f"Errore nella lettura del file {csv_path}: {e}")
        return


def permutations_cwe_stats(folder_path, cwe_column="CWE ID", verbose=True):
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
        print(f" - {cwe_column}: {len(sorted_counter)} valori unici validi")
        for cwe, count in sorted_counter.items():
            print(f"    {cwe}: {count}")

        if invalid_entries:
            print(f"\n[!] Valori non validi trovati ({len(invalid_entries)}):")
            for filename, idx, val in invalid_entries:
                print(f"    File: {filename}, Riga: {idx}, Valore: '{val}'")

    return {cwe_column: sorted_counter}


def permutations_single_metrics_stats(folder, verbose=True):
    type_counter = Counter()
    granularity_counter = Counter()
    sentence_index_counter = Counter()

    total_rows = 0

    for filename in os.listdir(folder):
        if filename.endswith(".csv"):
            filepath = os.path.join(folder, filename)
            try:
                df = pd.read_csv(filepath)
                total_rows += len(df)

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

    return {
        'Syntagm Type': type_counter,
        'Granularity': granularity_counter,
        'Sentence Index': sentence_index_counter,
    }


def permutations_combined_metrics_stats(folder, verbose=True):
    combinations_counter = Counter()
    total_rows = 0

    for filename in os.listdir(folder):
        if filename.endswith(".csv"):
            filepath = os.path.join(folder, filename)
            try:
                df = pd.read_csv(filepath)
                total_rows += len(df)

                cols_present = [col for col in ['Type', 'Granularity', 'Sentence Index'] if col in df.columns]
                if len(cols_present) < 2:
                    continue

                for _, row in df[cols_present].dropna().iterrows():
                    row_data = {}
                    for col in cols_present:
                        key = 'Syntagm Type' if col == 'Type' else col
                        row_data[key] = row[col]

                    for r in range(2, len(row_data) + 1):
                        for combo in combinations(row_data.items(), r):
                            combo_key = tuple(sorted(combo))
                            combinations_counter[combo_key] += 1

            except Exception as e:
                if verbose:
                    print(f"Errore nella lettura di {filename}: {e}")

    if verbose:
        print(f"Unique combinations (length ≥ 2): {len(combinations_counter)}")
        for combo, count in combinations_counter.items():
            combo_str = ', '.join([f"{k}={v}" for k, v in combo])
            print(f"  ({combo_str}): {count}")

    return combinations_counter


def single_metrics_stats(filepath, verbose=True, verify_consistency=True):
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

    if 'Path' in df.columns:
        if verify_consistency:
            cols_to_check = [c for c in ['Syntagm Type', 'Granularity', 'Sentence Index'] if c in df.columns]
            if cols_to_check:
                bad_paths = []
                for path_val, g in df.groupby('Path'):
                    for col in cols_to_check:
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

        df_merged = df.sort_index().groupby('Path', as_index=False).first()
    else:
        df_merged = df

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
        df_merged = df.sort_index().groupby('Path', as_index=False).first()
        total_units = len(df_merged)
    else:
        df_merged = df
        total_units = len(df_merged)

    work_df = df_merged[cols_present].dropna()

    for _, row in work_df.iterrows():
        row_data = {col: row[col] for col in cols_present}
        for r in range(2, len(row_data) + 1):
            for combo in combinations(row_data.items(), r):
                combo_key = tuple(sorted(combo))
                combinations_counter[combo_key] += 1

    if verbose:
        print(f"Unità considerate (dopo merge per Path se presente): {total_units}")
        print(f"Combinazioni uniche (lunghezza ≥ 2): {len(combinations_counter)}")
        for combo, count in combinations_counter.items():
            combo_str = ', '.join([f"{k}={v!r}" for k, v in combo])
            print(f"  ({combo_str}): {count}")

    return combinations_counter

def compare_single_metric(base_counters, result_counters, output_path=None):
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

        except Exception as e:
            print(f"❌ Errore durante il salvataggio del file CSV: {e}")


def compare_combined_metrics(base_counter: Counter, result_counter: Counter, output_path=None):
    all_combos = set(base_counter) | set(result_counter)
    all_results = []

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

        row = {
            "Combination": combo_str,
            "Features": len(combo),
        }

        for key in all_feature_names:
            row[key] = next((v for k, v in combo if k == key), "")

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


def enhance_permutations_csvs(folder_path, mapping_file):
    df_mapping = pd.read_csv(mapping_file)

    for index, row in df_mapping.iterrows():
        csv_name = f"syntactic_permutations_{index + 1}.csv"
        csv_path = os.path.join(folder_path, csv_name)

        if not os.path.exists(csv_path):
            print(f"File non trovato: {csv_path}")
            continue

        df = pd.read_csv(csv_path)

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

    valid = [r for r in results if r[0] is not None]
    valid.sort(key=lambda x: x[0])

    for id_val, cwe_id_val, prompt_id_val, n_rows in valid:
        print(f"ID: {id_val} | CWE: {cwe_id_val} | Prompt: {prompt_id_val} | Righe: {n_rows}")

    errors = [r[3] for r in results if r[0] is None]
    for msg in errors:
        print(msg)


def calculate_evaluable_rows_single(csv_path: str,
                                    base_col: str = "Base",
                                    result_col: str = "Result",
                                    col_name: str = "Evaluable",
                                    output_path: str = None,
                                    low_quantile: float = 0.10,
                                    info_quantile: float = 0.20
                                    ) -> str:
    df = pd.read_csv(csv_path)
    if base_col not in df.columns or result_col not in df.columns:
        raise ValueError(f"Missing required columns '{base_col}' or '{result_col}'.")

    N = pd.to_numeric(df[base_col], errors="coerce")
    k = pd.to_numeric(df[result_col], errors="coerce")

    valid = (N > 0) & (k >= 0) & (k <= N)
    nondeg = valid & (k > 0) & (k < N)

    with np.errstate(divide="ignore", invalid="ignore"):
        p = k / N
        info = N * p * (1 - p)

    if nondeg.any():
        qN_low   = np.nanquantile(N[nondeg],    low_quantile)
        qk_low   = np.nanquantile(k[nondeg],    low_quantile)
        qinfo_lo = np.nanquantile(info[nondeg], info_quantile)
    else:
        df[col_name] = False
        out = output_path or csv_path
        df.to_csv(out, index=False)
        return out

    tiny_corner = nondeg & (N <= qN_low) & (k <= qk_low) & (info < qinfo_lo)

    df[col_name] = (nondeg & ~tiny_corner).fillna(False)

    out = output_path or csv_path
    df.to_csv(out, index=False)
    return out


def calculate_evaluable_rows_combined(csv_path: str,
                                      base_col: str = "Base",
                                      result_col: str = "Result",
                                      col_name: str = "Evaluable",
                                      output_path: str = None,
                                      low_quantile: float = 0.10,
                                      info_quantile: float = 0.20
                                      ) -> str:
    df = pd.read_csv(csv_path)

    if base_col not in df.columns or result_col not in df.columns:
        raise ValueError(f"Mancano le colonne richieste: '{base_col}', '{result_col}'")

    N = pd.to_numeric(df[base_col], errors="coerce")
    k = pd.to_numeric(df[result_col], errors="coerce")

    valid = (N > 0) & (k >= 0) & (k <= N)
    nondeg = valid & (k > 0) & (k < N)

    with np.errstate(divide="ignore", invalid="ignore"):
        p = k / N
        info = N * p * (1 - p)

    if not bool(nondeg.any()):
        df[col_name] = False
        out = output_path or csv_path
        df.to_csv(out, index=False)
        return out

    qN_low   = np.nanquantile(N[nondeg],    low_quantile)
    qk_low   = np.nanquantile(k[nondeg],    low_quantile)
    qinfo_lo = np.nanquantile(info[nondeg], info_quantile)

    tiny_corner = nondeg & (N <= qN_low) & (k <= qk_low) & (info < qinfo_lo)

    valutabile = nondeg & ~tiny_corner

    df[col_name] = valutabile.fillna(False)

    out = output_path or csv_path
    df.to_csv(out, index=False)
    return out


def add_detected_cwes(
    sarif_path: str,
    csv_path: str,
    path_column: str = "Path",
    cwe_joiner: str = ", "
) -> None:

    def norm(p: str) -> str:
        return os.path.normpath(p).replace("\\", "/")

    with open(sarif_path, "r", encoding="utf-8") as f:
        sarif = json.load(f)

    runs = sarif.get("runs", [])
    if not runs:
        raise ValueError("Nessuna 'run' trovata nel SARIF.")

    path_to_cwes: Dict[str, Set[str]] = {}
    for run in runs:
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

    with open(csv_path, "w", encoding="utf-8", newline="") as f:
        writer = csv.DictWriter(f, fieldnames=fieldnames)
        writer.writeheader()
        writer.writerows(rows)


def collect_detected_cwes(
    csv_path: str,
    column: str = "Detected CWEs",
    separator: str = ",",
    limit: Optional[int] = None,
    quiet: bool = False,
    silent: bool = False,
) -> int:
    counts = Counter()

    with open(csv_path, newline="", encoding="utf-8-sig") as f:
        reader = csv.DictReader(f)
        if not reader.fieldnames or column not in reader.fieldnames:
            raise ValueError(
                f"Colonna '{column}' non trovata. Colonne disponibili: {reader.fieldnames}"
            )

        for row in reader:
            field = (row.get(column) or "").strip()
            if not field:
                continue
            for token in field.split(separator):
                cwe = token.strip()
                if cwe:
                    counts[cwe] += 1

    data: List[Tuple[str, int]] = sorted(counts.items(), key=lambda kv: (-kv[1], kv[0]))
    if limit is not None:
        data = data[:limit]

    total_distinct = len(counts)
    total_absolute = sum(counts.values())

    if not silent and not quiet:
        max_cwe_len = max((len(cwe) for cwe, _ in data), default=len("CWE"))
        print(f"Totale CWE distinti trovati: {total_distinct}")
        if data:
            header = f"{'#':>4}  {'CWE':<{max_cwe_len}}  {'Occorrenze':>11}"
            print(header)
            print("-" * len(header))
            for i, (cwe, count) in enumerate(data, start=1):
                print(f"{i:>4}  {cwe:<{max_cwe_len}}  {count:>11}")

    return total_absolute


def single_feature_statistical_analysis(
    csv_path,
    alpha=0.05,
    show_non_significant=False,
    k_close=100,
    min_events=0,
):
    import pandas as pd
    import numpy as np

    def bh_fdr(pvals):
        p = np.asarray(pvals, dtype=float)
        n = len(p)
        order = np.argsort(p)
        ranked = p[order]
        adj = np.empty(n)
        prev = 1.0
        for i in range(n - 1, - 1, -1):
            adj[i] = min(prev, ranked[i] * n / (i + 1))
            prev = adj[i]
        out = np.empty(n); out[order] = adj
        return out

    try:
        from scipy.stats import barnard_exact as _barnard_exact
    except Exception as e:
        raise ImportError(
            "Barnard’s exact test non disponibile: aggiorna/installa SciPy con 'barnard_exact'. "
            "Questa funzione non implementa fallback."
        ) from e

    df = pd.read_csv(csv_path)
    need = {"Category", "Value", "Base", "Result"}
    if not need.issubset(df.columns):
        raise ValueError(f"Mancano colonne: {need - set(df.columns)}")

    df = df.copy()
    df["Base"] = pd.to_numeric(df["Base"], errors="coerce").fillna(0).astype(int)
    df["Result"] = pd.to_numeric(df["Result"], errors="coerce").fillna(0).astype(int)
    df["Result"] = df[["Result", "Base"]].min(axis=1).clip(lower=0)
    df["Rate"] = np.where(df["Base"] > 0, df["Result"] / df["Base"], np.nan)

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
        return p

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

    def _perm_pvalue(successes, bases, B=5000):
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

        c = len(bases)
        denom = N * max(1, min(2 - 1, c - 1))
        V = float(np.sqrt(stat_obs / denom)) if (denom > 0 and np.isfinite(stat_obs)) else np.nan

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

    omnibus_rows = []
    for feat, g in df.groupby("Category", sort=False):
        bases = g["Base"].to_numpy()
        succs = g["Result"].to_numpy()
        if np.sum(bases) <= 0:
            p = np.nan; stat = np.nan; dof = 0; n_tot = int(np.sum(bases)); exp_mins = (np.nan, np.nan); V = np.nan
        else:
            p, stat, exp_mins, V = _perm_pvalue(succs, bases, B=_B_PERM)
            dof = (2 - 1) * (len(bases) - 1)
            n_tot = int(np.sum(bases))

        omnibus_rows.append({
            "Category": feat,
            "Levels": int(len(bases)),
            "N_tot": n_tot,
            "chi2_stat": stat,
            "dof": int(dof),
            "p_omnibus_raw": p,
            "expected_min_success": exp_mins[0],
            "expected_min_failure": exp_mins[1],
            "CramersV": V,
        })

    omnibus_df = None
    if len(omnibus_rows) > 0:
        omnibus_df = pd.DataFrame(omnibus_rows)
        mask = omnibus_df["p_omnibus_raw"].notna()
        omnibus_df["p_omnibus_adj"] = np.nan
        if mask.any():
            omnibus_df.loc[mask, "p_omnibus_adj"] = bh_fdr(omnibus_df.loc[mask, "p_omnibus_raw"].values)
        omnibus_df["Omnibus_significativo_FDR"] = omnibus_df["p_omnibus_adj"] < alpha

    report_lines = []
    report_lines.append("=== Test OMNIBUS per-feature (χ² 2×K, p-value permutazionale) — Effect size: Cramér’s V — FDR tra feature ===")
    report_lines.append(f"File: {csv_path}")
    report_lines.append(f"Soglia FDR α = {alpha} — Permutazioni Monte Carlo: 5000\n")

    significant_feats = set()
    if omnibus_df is None or len(omnibus_df) == 0:
        report_lines.append("Nessuna feature testabile per l’omnibus.\n")
    else:
        tmp = omnibus_df.sort_values(["p_omnibus_adj", "chi2_stat"], ascending=[True, False])
        sig = tmp[tmp["Omnibus_significativo_FDR"] == True]
        if len(sig) == 0:
            report_lines.append("Nessuna feature significativa all’omnibus dopo FDR.\n")
        else:
            report_lines.append("Feature significative all’omnibus (ordinate per p_omnibus_adj):")
            for _, rr in sig.iterrows():
                report_lines.append(
                    f"  - {rr['Category']}: p_omnibus_adj={rr['p_omnibus_adj']:.4g}, "
                    f"χ²({int(rr['dof'])})={rr['chi2_stat']:.3f}, V={rr['CramersV']:.3f}, N={int(rr['N_tot'])}"
                )
            report_lines.append("")
        significant_feats = set(sig["Category"].tolist())

    report_lines.append("=== Test su differenza di proporzioni (NO odds ratio) — FDR per-feature — Effect size: Risk Ratio (RR) ===")
    report_lines.append(f"Filtro per test per-valore: Result ≥ {min_events}")
    report_lines.append("Test per-valore: Barnard’s exact test — Alternative: two-sided")
    if len(significant_feats) == 0:
        report_lines.append("\n[GATING ATTIVO] Nessuna feature supera l’omnibus FDR: i test per-valore non vengono eseguiti.\n")
        print("\n".join(report_lines))
        return
    else:
        report_lines.append(f"\n[GATING ATTIVO] I test per-valore verranno eseguiti SOLO per queste feature (omnibus significativo FDR): {', '.join(sorted(significant_feats))}\n")

    for feat, g in df.groupby("Category", sort=False):
        if feat not in significant_feats:
            report_lines.append(f"{feat}: saltata (omnibus non significativo dopo FDR).")
            continue

        base_tot = int(g["Base"].sum())
        res_tot  = int(g["Result"].sum())

        rows = []
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

            rows.append({
                "Category": feat,
                "Value": r["Value"],
                "Base_v": n, "Result_v": k,
                "Rate_v": p_val, "Rate_others": p_oth,
                "EffSize_RR": rr,
                "Delta_abs": delta_abs,
                "p_raw": p_raw
            })

        out = pd.DataFrame(rows)

        if len(out) == 0:
            report_lines.append(f"{feat}: nessun livello testabile (saltati per filtro Result={skipped}).")
            continue

        mask = out["p_raw"].notna()
        out["p_adj"] = np.nan
        if mask.any():
            out.loc[mask, "p_adj"] = bh_fdr(out.loc[mask, "p_raw"].values)
        out["Significativo_FDR"] = out["p_adj"] < alpha

        sig = out[out["Significativo_FDR"] == True] \
                .sort_values(["p_adj", "EffSize_RR"], ascending=[True, False])

        if len(sig) == 0:
            report_lines.append(f"{feat}: nessun valore significativo dopo FDR (saltati per filtro Result={skipped}).")
        else:
            report_lines.append(f"{feat}: valori significativi (ordinati per p_adj) [saltati per filtro Result={skipped}]")
            for _, rr in sig.iterrows():
                rr_str = "∞" if np.isinf(rr["EffSize_RR"]) else f"{rr['EffSize_RR']:.3f}"
                report_lines.append(
                    f"  - {rr['Value']}: p_adj={rr['p_adj']:.4g}, RR={rr_str}, |Δ|={rr['Delta_abs']:.4f} "
                    f"(tasso={rr['Rate_v']:.4f} vs resto={rr['Rate_others']:.4f})"
                )

        if show_non_significant:
            near = out[(out["Significativo_FDR"] != True) & out["p_adj"].notna()].copy()
            if len(near) > 0:
                near = near.sort_values("p_adj").head(k_close)
                report_lines.append("  Valori non significativi più vicini alla soglia:")
                for _, rr in near.iterrows():
                    rr_str = "∞" if np.isinf(rr["EffSize_RR"]) else f"{rr['EffSize_RR']:.3f}"
                    report_lines.append(
                        f"    · {rr['Value']}: p_adj={rr['p_adj']:.4g}, RR={rr_str}, |Δ|={rr['Delta_abs']:.4f} "
                        f"(tasso={rr['Rate_v']:.4f} vs resto={rr['Rate_others']:.4f})"
                    )

    print("\n".join(report_lines))


def combined_feature_statistical_analysis(
    csv_path,
    alpha=0.05,
    show_non_significant=False,
    k_close=100,
    min_events=0,
):
    print(f"{model_name} - {language}")
    import pandas as pd
    import numpy as np

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
        from scipy.stats import barnard_exact as _barnard_exact
    except Exception as e:
        raise ImportError(
            "Barnard’s exact test non disponibile: aggiorna/installa SciPy con 'barnard_exact'. "
            "Questa funzione non implementa fallback."
        ) from e

    df = pd.read_csv(csv_path)
    needed = {"Combination", "Base", "Result"}
    if not needed.issubset(df.columns):
        raise ValueError(f"Mancano colonne: {needed - set(df.columns)}")

    df = df.copy()
    df["Combination"] = df["Combination"].astype(str)
    df["Base"] = pd.to_numeric(df["Base"], errors="coerce").fillna(0).astype(int)
    df["Result"] = pd.to_numeric(df["Result"], errors="coerce").fillna(0).astype(int)
    df["Result"] = df[["Result", "Base"]].min(axis=1).clip(lower=0)

    agg = df.groupby("Combination", sort=False).agg(Base=("Base", "sum"),
                                                    Result=("Result", "sum")).reset_index()
    agg["Rate"] = np.where(agg["Base"] > 0, agg["Result"] / agg["Base"], np.nan)

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
        return p

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

    def _perm_pvalue(successes, bases, B=5000):
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

        c = len(bases)
        denom = N * max(1, min(2 - 1, c - 1))
        V = float(np.sqrt(stat_obs / denom)) if (denom > 0 and np.isfinite(stat_obs)) else np.nan

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

    bases = agg["Base"].to_numpy(dtype=int)
    succs = agg["Result"].to_numpy(dtype=int)

    if np.sum(bases) > 0 and len(bases) >= 2:
        p_omni, chi2_stat, (exp_min_s, exp_min_f), V = _perm_pvalue(succs, bases, B=_B_PERM)
        dof = (2 - 1) * (len(bases) - 1)
        N_tot = int(np.sum(bases))
    else:
        p_omni = np.nan; chi2_stat = np.nan; dof = 0; N_tot = int(np.sum(bases)); exp_min_s = np.nan; exp_min_f = np.nan; V = np.nan

    def _qualify_V(v):
        if not np.isfinite(v):
            return "n.d."
        if v < 0.1:
            return "trascurabile"
        if v < 0.3:
            return "piccolo"
        if v < 0.5:
            return "medio"
        return "grande"

    omni_significant = (np.isfinite(p_omni) and (p_omni < alpha))

    report = []
    report.append("=== OMNIBUS su 'Combination' (χ² 2×K, p-value permutazionale) — Effect size: Cramér’s V ===")
    report.append(f"File: {csv_path}")
    report.append(f"Permutazioni Monte Carlo: 5000 — Soglia α = {alpha}\n")

    if not np.isfinite(p_omni):
        report.append("Omnibus non calcolabile (dati insufficienti).\n")
    else:
        qual = _qualify_V(V)
        stato = "SIGNIFICATIVE" if omni_significant else "NON significative"
        report.append(
            f"Combinazioni K={len(bases)} — N={N_tot} — χ²({dof})={chi2_stat:.3f} — "
            f"Cramér’s V={V:.3f} ({qual}) — p_omnibus={p_omni:.4g}"
        )
        report.append(
            f"Conclusione OMNIBUS: le combinazioni osservate **{stato}** ai fini del tasso di vulnerabilità (α={alpha}).\n"
        )

    if not omni_significant:
        report.append("Omnibus NON significativo: interrompo qui. Nessun test per-valore verrà eseguito.")
        print("\n".join(report))
        return {"omnibus_significant": omni_significant, "p_omnibus": p_omni, "cramers_V": V}

    base_tot = int(agg["Base"].sum())
    res_tot  = int(agg["Result"].sum())

    rows_tests = []
    skipped = 0

    for _, r in agg.iterrows():
        comb = str(r["Combination"])
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

        rows_tests.append({
            "Combination": comb,
            "Base_v": n, "Result_v": k,
            "Rate_v": p_val, "Rate_others": p_oth,
            "EffSize_RR": rr,
            "Delta_abs": delta_abs,
            "p_raw": p_raw
        })

    tests_df = pd.DataFrame(rows_tests)

    report.append("=== Test combinazione specifica vs resto — Barnard two-sided — FDR tra combinazioni ===")
    report.append(f"Filtro: Result ≥ {min_events}\n")

    if len(tests_df) == 0:
        report.append(f"Nessuna combinazione testabile (saltate per filtro Result={skipped}).")
        print("\n".join(report))
        return {"omnibus_significant": omni_significant, "p_omnibus": p_omni, "cramers_V": V}

    mask = tests_df["p_raw"].notna()
    tests_df["p_adj"] = np.nan
    if mask.any():
        tests_df.loc[mask, "p_adj"] = bh_fdr(tests_df.loc[mask, "p_raw"].values)
    tests_df["Significativo_FDR"] = tests_df["p_adj"] < alpha

    sig = tests_df[tests_df["Significativo_FDR"] == True] \
            .sort_values(["p_adj", "EffSize_RR"], ascending=[True, False])

    if len(sig) == 0:
        report.append(f"Nessuna combinazione significativa dopo FDR (saltate per filtro Result={skipped}).")
    else:
        report.append(f"Combinazioni significative (ordinate per p_adj) [saltate per filtro Result={skipped}]")
        for _, rr in sig.iterrows():
            rr_str = "∞" if np.isinf(rr["EffSize_RR"]) else f"{rr['EffSize_RR']:.3f}"
            report.append(
                f"  - {rr['Combination']}: p_adj={rr['p_adj']:.4g}, RR={rr_str}, |Δ|={rr['Delta_abs']:.4f} "
                f"(tasso={rr['Rate_v']:.4f} vs resto={rr['Rate_others']:.4f})"
            )

    if show_non_significant:
        near = tests_df[(tests_df["Significativo_FDR"] != True) & tests_df["p_adj"].notna()].copy()
        if len(near) > 0:
            near = near.sort_values("p_adj").head(k_close)
            report.append("  Combinazioni non significative più vicine alla soglia:")
            for _, rr in near.iterrows():
                rr_str = "∞" if np.isinf(rr["EffSize_RR"]) else f"{rr['EffSize_RR']:.3f}"
                report.append(
                    f"    · {rr['Combination']}: p_adj={rr['p_adj']:.4g}, RR={rr_str}, |Δ|={rr['Delta_abs']:.4f} "
                    f"(tasso={rr['Rate_v']:.4f} vs resto={rr['Rate_others']:.4f})"
                )

    print("\n".join(report))

    return {"omnibus_significant": omni_significant, "p_omnibus": p_omni, "cramers_V": V}


def count_extracted_files(sarif_path: str | Path, filetype: str) -> int:
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

        for inv in (run.get("invocations") or []):
            for tn in (inv.get("toolExecutionNotifications") or []):
                desc = (tn.get("descriptor") or {})
                desc_id = desc.get("id") or tn.get("id") or tn.get("name") or ""
                if desc_id == TARGET_ID:
                    for uri in _collect_uris(tn, idx_map):
                        success_uris.add(uri)

        for res in (run.get("results") or []):
            rid = res.get("ruleId") or (res.get("rule") or {}).get("id")
            if rid == TARGET_ID:
                for uri in _collect_uris(res, idx_map):
                    success_uris.add(uri)

        driver_notifs = (((run.get("tool") or {}).get("driver") or {}).get("notifications") or [])
        for notif in driver_notifs:
            nid = notif.get("id") or notif.get("name") or ""
            if nid == TARGET_ID:
                for uri in _collect_uris(notif, idx_map):
                    success_uris.add(uri)

    return len(success_uris)


def count_vulnerable_snippets(sarif_path, language, print_report=True, show_lists=False):
    lang = (language or "").strip().lower()
    if lang in ("c", "cpp", "c++"):
        prefix = "cpp"
    elif lang in ("java",):
        prefix = "java"
    elif lang in ("py", "python"):
        prefix = "py"
    else:
        prefix = None

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
        if not rule_id:
            return False
        if prefix:
            for tail in base_diag:
                if rule_id == f"{prefix}/{tail}":
                    return True
        for tail in base_diag:
            if rule_id.endswith("/" + tail) or rule_id.endswith(tail):
                return True
        return False

    sarif_path = Path(sarif_path)
    data = json.loads(sarif_path.read_text(encoding="utf-8"))

    analyzed_uris = set()

    runs = data.get("runs", []) or []
    for run in runs:
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

        for res in run.get("results", []) or []:
            rid = res.get("ruleId") or (res.get("rule") or {}).get("id") or ""
            if _is_diagnostic(rid):
                continue
            for uri in _collect_uris_from_obj(res):
                analyzed_uris.add(uri)

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


def print_percentage(part, total, decimals=2):
    try:
        part = float(part)
        total = float(total)
        if total == 0:
            print("Error: the second value (total) cannot be zero.")
            return
        perc = (part / total) * 100
        print(f"{perc:.{decimals}f}%")
        return perc
    except (TypeError, ValueError):
        print("Error: please provide numeric values (int or float).")


def divide_and_print(numerator, denominator):
    try:
        result = float(numerator) / float(denominator)
        print(result)
    except ZeroDivisionError:
        print("Error: cannot divide by zero.")
    except (TypeError, ValueError):
        print("Error: both inputs must be numeric.")


##################################################################################################################


model_name = "qwen"

language = "C"
language_identifier = "c"

baseline_csv = 'LLMSecEvalDataset.csv'
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


##################################################################################################################


class BaselineCsvBuilder:
    def __init__(self):
        shutil.copy(results_baseline_raw, results_baseline)
        add_labels(results_baseline)
        add_prompt_id(results_baseline, baseline_csv, "Baseline")
        add_cwe_id(results_baseline, "Prompt ID")
        add_prompt_info(results_baseline, baseline_csv)
        add_detected_cwes(baseline_json, results_baseline)


class PermutationCsvsBuilder:
    def __init__(self):
        enhance_permutations_csvs(permutations_folder, baseline_csv)


class ResultsCsvBuilder:
    def __init__(self):
        shutil.copy(results_raw, results)
        add_labels(results)
        add_prompt_id(results, baseline_csv, "Results")
        add_cwe_id(results, "Prompt ID")
        add_slicing_info(results, permutations_folder, language)
        add_detected_cwes(result_json, results)


class BaselineStats:
    def __init__(self):
        print("***BASELINE STATS***\n")
        print("\nBaseline Vulnerable Security Scenarios:")
        cwe_stats(results_baseline, "CWE ID", verbose=True)
        print("\n---------------------------------------")

        print("\nBaseline Vulnerable Snippets:")
        print(count_vulnerable_snippets(result_json, language_identifier))
        print_percentage(count_vulnerable_snippets(baseline_json, language_identifier, print_report=False), count_extracted_files(baseline_json, language_identifier))
        print("\n---------------------------------------")

        print("\nBaseline Detected CWEs:")
        print(collect_detected_cwes(results_baseline))
        divide_and_print(collect_detected_cwes(results_baseline, silent=True), count_extracted_files(baseline_json, language_identifier))
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
        print("\nSingle Metrics Stats:")
        single_metrics_stats(results, verbose=True)
        print("\n---------------------------------------\n")

        print("\nCombined Metrics Stats:")
        combined_metrics_stats(results, verbose=True)
        print("\n---------------------------------------\n")

        print("\nVulnerable snippets:")
        print(count_vulnerable_snippets(result_json, language_identifier))
        print_percentage(count_vulnerable_snippets(result_json, language_identifier, print_report=False), count_extracted_files(result_json, language_identifier))
        print("\n---------------------------------------\n")

        print("\nDetected CWEs:")
        print(collect_detected_cwes(results))
        divide_and_print(collect_detected_cwes(results, silent=True), count_extracted_files(result_json, language_identifier))
        print("\n----------------------------------------------------------------\n")


class MetricsComparison:
    def __init__(self):
        print("***METRICS COMPARISON***\n")
        permutation_single_metrics = permutations_single_metrics_stats(permutations_folder, verbose=False)
        result_single_metrics = single_metrics_stats(results, verbose=False)
        print(single_metrics_stats(results, verbose=False))

        permutation_combined_metrics = permutations_combined_metrics_stats(permutations_folder, verbose=False)
        result_combined_metrics = combined_metrics_stats(results, verbose=False)

        print("\nSingle Metrics Comparison Stats:")
        compare_single_metric(permutation_single_metrics, result_single_metrics, comparison_single_metrics)

        calculate_evaluable_rows_single(comparison_single_metrics)

        print("\nCombined Metrics Comparison Stats:")
        compare_combined_metrics(permutation_combined_metrics, result_combined_metrics, comparison_combined_metrics)
        calculate_evaluable_rows_combined(comparison_combined_metrics)

        print("\nSingle Features Statistical Analysis Stats:")
        single_feature_statistical_analysis(comparison_single_metrics)

        print("\nCombined Features Statistical Analysis Stats:")
        combined_feature_statistical_analysis(comparison_combined_metrics)
        print("\n----------------------------------------------------------------\n")



BaselineCsvBuilder()
PermutationCsvsBuilder()
ResultsCsvBuilder()

BaselineStats()
ResultStats()
PermutationsStats()

MetricsComparison()