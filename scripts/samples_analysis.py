import csv
import json
import math
import os
import re
import shutil
import unicodedata
from collections import Counter
from itertools import combinations
from pathlib import Path
from typing import Dict, Set, List, Tuple, Sequence, Optional

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


def analyze_single_feature_significance(csv_path: str, alpha: float = 0.05, top_n: int = 100, verbose: bool = True):
    import numpy as np
    import pandas as pd
    from scipy.stats import chi2_contingency, fisher_exact
    from scipy.stats import chi2 as _chi2

    def _log(*args, **kwargs):
        if verbose:
            print(*args, **kwargs)

    df = pd.read_csv(csv_path)
    required = {"Category", "Value", "Base", "Result"}
    if not required.issubset(df.columns):
        raise ValueError(f"CSV must contain columns: {sorted(required)}")
    df = df.copy()
    df["Category"] = df["Category"].astype(str).str.strip()
    df["Value"] = df["Value"].astype(str).str.strip()
    df["Base"] = pd.to_numeric(df["Base"])
    df["Result"] = pd.to_numeric(df["Result"])

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

    rows = []
    for cat, sub in df.groupby("Category", sort=False):
        N = int(sub["Base"].sum())
        V = int(sub["Result"].sum())
        for _, r in sub.iterrows():
            base = int(r["Base"])
            a = int(r["Result"])
            b = base - a
            c = V - a
            d = (N - base) - c
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

    per_value_df["q_value"] = _bh_fdr(np.nan_to_num(per_value_df["p_value"], nan=1.0))
    per_value_df["Significant"] = per_value_df["q_value"] <= alpha

    per_value_df = per_value_df.sort_values(
        ["Significant", "q_value", "Rate_diff", "OddsRatio"],
        ascending=[False, True, False, False]
    ).reset_index(drop=True)

    global_rows = []
    for cat, sub in df.groupby("Category", sort=False):
        sub = sub.copy()
        sub["Base"] = pd.to_numeric(sub["Base"], errors="coerce")
        sub["Result"] = pd.to_numeric(sub["Result"], errors="coerce")

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

        if tot_vuln == 0:
            global_rows.append({"Category": cat, "Chi2": 0.0, "df": m - 1, "p_value": 1.0})
            continue

        r = tot_vuln / tot_base
        expected = sub["Base"] * r
        observed = sub["Result"]

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

    def pct(x):
        return f"{100*x:.1f}%" if np.isfinite(x) else "NA"

    _log("\n" + "="*80)
    _log("Statistical Analysis — Syntagm Features and Vulnerability")
    _log("="*80)

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

    notsig = per_value_df[~per_value_df["Significant"]].copy()
    if verbose and len(notsig):
        notsig["_abs_diff"] = notsig["Rate_diff"].abs()
        trending = notsig.sort_values(["_abs_diff", "p_value"], ascending=[False, True]).head(top_n)
        _log("\n⚠ Trending but not significant (largest rate differences; low q but > α)")
        for _, r in trending.iterrows():
            direction = "higher" if r["Rate_diff"] > 0 else "lower"
            _log(f"  [{r['Category']}] {r['Value']}: "
                  f"{pct(r['Rate_with'])} vs {pct(r['Rate_without'])} ({direction} than baseline by {pct(abs(r['Rate_diff']))}); "
                  f"OR={r['OddsRatio']:.2f}, p={r['p_value']:.3g}, q={r['q_value']:.3g} ({r['Test']})")

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
    import numpy as np
    import pandas as pd
    from scipy.stats import chi2_contingency, fisher_exact
    from scipy.stats import chi2 as _chi2

    df = pd.read_csv(csv_path)
    required = {"Combination", "Features", "Base", "Result"}
    if not required.issubset(df.columns):
        missing = sorted(required - set(df.columns))
        present = sorted(map(str, df.columns))
        if verbose:
            print(f"[Schema CSV non valido] File: {csv_path}\n  Mancanti: {missing}\n  Presenti: {present}")
        raise ValueError(f"{csv_path}: CSV must contain columns {sorted(required)} (missing: {missing})")

    df = df.copy()
    df["Combination"] = df["Combination"].astype(str).str.strip()
    df["Features"] = pd.to_numeric(df["Features"], errors="coerce").astype("Int64")
    df["Base"] = pd.to_numeric(df["Base"])
    df["Result"] = pd.to_numeric(df["Result"])

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

    rows = []
    for k, sub in df.groupby("Features", dropna=False, sort=False):
        N = int(sub["Base"].sum())
        V = int(sub["Result"].sum())
        for _, r in sub.iterrows():
            base = int(r["Base"])
            a = int(r["Result"])
            b = base - a
            c = V - a
            d = (N - base) - c
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

    per_combo_df["q_value"] = _bh_fdr(np.nan_to_num(per_combo_df["p_value"], nan=1.0))
    per_combo_df["Significant"] = per_combo_df["q_value"] <= alpha

    per_combo_df = per_combo_df.sort_values(
        ["Significant", "q_value", "Rate_diff", "OddsRatio"],
        ascending=[False, True, False, False]
    ).reset_index(drop=True)

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


def collect_detected_cwes_merged(
    csv_path_1: str,
    csv_path_2: str,
    csv_path_3: str,
    column: str = "Detected CWEs",
    separator: str = ",",
    top_k: int = 5,
    quiet: bool = False,
    silent: bool = False,
) -> float:
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

    c1 = _count_cwes_in_csv(csv_path_1)
    c2 = _count_cwes_in_csv(csv_path_2)
    c3 = _count_cwes_in_csv(csv_path_3)

    all_cwes = set(c1) | set(c2) | set(c3)

    averaged: List[Tuple[str, float]] = []
    for cwe in all_cwes:
        mean_val = (c1.get(cwe, 0) + c2.get(cwe, 0) + c3.get(cwe, 0)) / 3.0
        averaged.append((cwe, mean_val))

    averaged.sort(key=lambda kv: (-kv[1], kv[0]))

    top = averaged[:top_k]

    t1 = sum(c1.values())
    t2 = sum(c2.values())
    t3 = sum(c3.values())
    mean_total = (t1 + t2 + t3) / 3.0

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

    def _to_float(series: pd.Series, decimal: str, treat_percent: bool = True) -> tuple[pd.Series, bool]:
        s_raw = series.astype(str)
        s = s_raw.str.strip()

        had_percent = False
        if treat_percent:
            had_percent = s.str.contains("%", regex=False, na=False)
            s = s.str.replace("%", "", regex=False)

        if decimal == ",":
            s = s.str.replace(".", "", regex=False)
            s = s.str.replace(",", ".", regex=False)
        else:
            s = s.str.replace(",", "", regex=False)

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
        df["Result"],    _ = _to_float(df["Result"],    decimal, treat_percent=True)
        df["Base"],      _ = _to_float(df["Base"],      decimal, treat_percent=False)

        df = df.dropna(subset=["Frequency", "Result", "Base"])

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

    merged["Base"] = merged["Base_a"]

    merged["Frequency"] = merged[["Frequency_a", "Frequency_b", "Frequency_c"]].mean(axis=1)
    merged["Result"]    = merged[["Result_a", "Result_b", "Result_c"]].mean(axis=1)

    out = merged[["Category", "Value", "Base", "Result", "Frequency"]]

    if sort:
        out = out.sort_values(["Category", "Value"]).reset_index(drop=True)

    def _format_number(x: float, decimal: str, sig: int = 6) -> str:
        s = f"{x:.{sig}g}"
        if decimal == ",":
            s = s.replace(".", ",")
        return s

    def _fmt_base(x: float) -> str:
        if pd.isna(x):
            return ""
        if abs(x - round(x)) < 1e-9:
            return f"{int(round(x))}"
        return _format_number(float(x), decimal)

    out["Base"] = out["Base"].apply(_fmt_base)

    def _round_half_away_from_zero(v: float) -> int:
        if pd.isna(v):
            return ""
        return int(math.floor(v + 0.5)) if v >= 0 else int(math.ceil(v - 0.5))

    out["Result"] = out["Result"].apply(_round_half_away_from_zero).astype(str)

    def _fmt_pct(x: float) -> str:
        val = x * 100.0
        s = f"{val:.2f}"
        if decimal == ",":
            s = s.replace(".", ",")
        return s + "%"

    out["Frequency"] = out["Frequency"].apply(_fmt_pct)

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

    META_COLS = ["Features", "Granularity", "Sentence Index", "Syntagm Type"]

    def _normalize_combo(s: str) -> str:
        s = unicodedata.normalize("NFKC", str(s)).strip()
        s = " ".join(s.split())
        return s

    def _parse_value(series: pd.Series) -> pd.Series:
        raw = series.astype(str)
        has_percent = raw.str.contains("%", na=False)
        clean = raw.str.replace("%", "", regex=False).str.strip()
        clean = clean.str.replace(",", ".", regex=False)
        num = pd.to_numeric(clean, errors="coerce")
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

    freq_cols = [c for c in merged.columns if c.startswith("Frequency_")]
    merged["Frequency"] = merged[freq_cols].mean(axis=1)

    result_cols = [c for c in merged.columns if c.startswith("Result_")]
    merged["Result"] = merged[result_cols].mean(axis=1)
    merged["Result"] = merged["Result"].round().astype("Int64")

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

    for col in META_COLS:
        if col not in merged.columns:
            merged[col] = pd.NA
    merged["Sentence Index"] = pd.to_numeric(merged["Sentence Index"], errors="coerce").astype("Int64")

    out_cols = ["Combination"] + META_COLS + ["Base", "Result", "Frequency"]
    out = merged[out_cols]

    if sort:
        out = out.sort_values(["Combination"]).reset_index(drop=True)

    def _format_pct(x: float) -> str:
        s = f"{x * 100:.2f}%"
        return s.replace(".", ",") if decimal == "," else s

    to_write = out.copy()
    to_write["Frequency"] = to_write["Frequency"].map(lambda v: _format_pct(float(v)) if pd.notna(v) else "")

    to_write.to_csv(csv_out, sep=sep, index=False, encoding=encoding)

    for _, row in out.iterrows():
        freq_str = _format_pct(float(row["Frequency"])) if pd.notna(row["Frequency"]) else ""
        print(f"{row['Combination']}: Result={row['Result']} | Frequency={freq_str}")

    return out


def single_feature_statistical_analysis_merged(
    csv_path_1,
    csv_path_2,
    csv_path_3,
    alpha=0.05,
    show_non_significant_close=False,
    k_close=5,
    min_events=0
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
        for i in range(n - 1, -1, -1):
            adj[i] = min(prev, ranked[i] * n / (i + 1))
            prev = adj[i]
        out = np.empty(n); out[order] = adj
        return out

    try:
        from scipy.stats import barnard_exact as _barnard_exact
        from scipy.stats import chi2
    except Exception as e:
        raise ImportError(
            "SciPy con 'barnard_exact' è richiesto. Installa/aggiorna SciPy."
        ) from e

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

        sig_omni_feats = set(
            omnibus_df.loc[omnibus_df["Omnibus_significativo_FDR"] == True, "Category"]
        )

        pv_rows = []
        if len(sig_omni_feats) > 0:
            for feat, g in df.groupby("Category", sort=False):
                if feat not in sig_omni_feats:
                    continue

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

    omni1, pv1 = _analyze_one(csv_path_1)
    omni2, pv2 = _analyze_one(csv_path_2)
    omni3, pv3 = _analyze_one(csv_path_3)

    sig1 = set(omni1.loc[omni1["Omnibus_significativo_FDR"] == True, "Category"])
    sig2 = set(omni2.loc[omni2["Omnibus_significativo_FDR"] == True, "Category"])
    sig3 = set(omni3.loc[omni3["Omnibus_significativo_FDR"] == True, "Category"])
    common_omni = sorted(sig1 & sig2 & sig3)

    def _fisher_p(p_list):
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

    pv1_sig = pv1[pv1["Significativo_FDR"] == True]
    pv2_sig = pv2[pv2["Significativo_FDR"] == True]
    pv3_sig = pv3[pv3["Significativo_FDR"] == True]

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
        for _, r in per_value_common_df.head(50).iterrows():
            rr_str = "∞" if np.isinf(r["RR_pooled"]) else f"{r['RR_pooled']:.3f}"
            lines.append(f"  - {r['Category']} :: {r['Value']}: p_Fisher={r['p_combined_Fisher']:.4g}, "
                         f"RR_pooled={rr_str}, tasso={r['Rate_v_pooled']:.4f} vs resto={r['Rate_others_pooled']:.4f} "
                         f"(Base={int(r['Base_v_pooled'])}/{int(r['Base_others_pooled'])})")
        if len(per_value_common_df) > 50:
            lines.append(f"... ({len(per_value_common_df)-50} righe ulteriori non mostrate)")

    print("\n".join(lines))

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
    show_non_significant_close=False,
    k_close=5,
    min_events=0,
):
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
        from scipy.stats import chi2
    except Exception as e:
        raise ImportError(
            "SciPy con 'barnard_exact' è richiesto. Installa/aggiorna SciPy (>=1.9)."
        ) from e

    def fisher_method(pvals):
        pvals = [p for p in pvals if np.isfinite(p) and p > 0]
        if len(pvals) == 0:
            return np.nan
        X = -2.0 * np.sum(np.log(pvals))
        df = 2 * len(pvals)
        return float(1 - chi2.cdf(X, df))

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

    res1 = analyze_one(csv_path_1)
    res2 = analyze_one(csv_path_2)
    res3 = analyze_one(csv_path_3)

    all_sig = res1["omnibus_significant"] and res2["omnibus_significant"] and res3["omnibus_significant"]

    omnibus_details = {
        "per_file": [
            {"file": res1["file"], "p_omnibus": res1["p_omnibus"], "cramers_V": res1["cramers_V"], "N_tot": res1["N_tot"]},
            {"file": res2["file"], "p_omnibus": res2["p_omnibus"], "cramers_V": res2["cramers_V"], "N_tot": res2["N_tot"]},
            {"file": res3["file"], "p_omnibus": res3["p_omnibus"], "cramers_V": res3["cramers_V"], "N_tot": res3["N_tot"]},
        ]
    }

    if all_sig:
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

    set1 = set(res1["sig_df"]["Combination"])
    set2 = set(res2["sig_df"]["Combination"])
    set3 = set(res3["sig_df"]["Combination"])
    comuni = sorted(list(set1 & set2 & set3))

    rows_common = []
    if len(comuni) > 0:
        def row_of(df, comb):
            r = df[df["Combination"] == comb]
            return r.iloc[0].to_dict() if len(r) else None

        for comb in comuni:
            r1 = row_of(res1["tests_df"], comb)
            r2 = row_of(res2["tests_df"], comb)
            r3 = row_of(res3["tests_df"], comb)
            n_v = sum([r["Base_v"]  for r in (r1,r2,r3)])
            k_v = sum([r["Result_v"] for r in (r1,r2,r3)])
            base_tot = sum([r["Base_tot"] for r in (r1,r2,r3)])
            res_tot  = sum([r["Result_tot"] for r in (r1,r2,r3)])
            base_oth = base_tot - n_v
            res_oth  = res_tot  - k_v

            rate_v_pooled = (k_v / n_v) if n_v > 0 else np.nan
            rate_o_pooled = (res_oth / base_oth) if base_oth > 0 else np.nan
            rr_pooled = (np.inf if (rate_o_pooled == 0 and rate_v_pooled > 0)
                         else (rate_v_pooled / rate_o_pooled if rate_o_pooled > 0 else 1.0))
            delta_pooled = abs((rate_v_pooled if np.isfinite(rate_v_pooled) else 0.0) -
                               (rate_o_pooled if np.isfinite(rate_o_pooled) else 0.0))
            p_barnard_pooled = barnard_p(k_v, n_v, res_oth, base_oth)

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

                "p_adj_file1": r1["p_raw"],
                "p_adj_file2": r2["p_raw"],
                "p_adj_file3": r3["p_raw"],

                "Rate_v_file1": r1["Rate_v"], "Rate_o_file1": r1["Rate_others"],
                "Rate_v_file2": r2["Rate_v"], "Rate_o_file2": r2["Rate_others"],
                "Rate_v_file3": r3["Rate_v"], "Rate_o_file3": r3["Rate_others"],

                "Base_v_sum": n_v, "Result_v_sum": k_v,
                "Base_oth_sum": base_oth, "Result_oth_sum": res_oth,

                "Rate_v_weighted": rate_v_weighted,
                "Rate_others_weighted": rate_o_weighted,

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


def count_extracted_files_merged(
    sarif_paths: Sequence[str | Path],
    filetype: str,
) -> int:
    if len(sarif_paths) != 3:
        raise ValueError(f"Attesi esattamente 3 file, ricevuti {len(sarif_paths)}.")

    counts: list[int] = []
    for p in sarif_paths:
        counts.append(count_extracted_files(p, filetype))

    return sum(counts) // 3


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


def count_vulnerable_snippets_merged(sarif_path_1, sarif_path_2, sarif_path_3, language, print_report=True):
    values = []
    for p in (sarif_path_1, sarif_path_2, sarif_path_3):
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
    try:
        result = float(numerator) / float(denominator)
        print(result)
    except ZeroDivisionError:
        print("Error: cannot divide by zero.")
    except (TypeError, ValueError):
        print("Error: both inputs must be numeric.")


##################################################################################################################


model_name = "athene"

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


##################################################################################################################


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


class BaselineStats:
    def __init__(self):
        print("***BASELINE STATS***\n")
        vulnerable_snippets = count_vulnerable_snippets_merged(baseline_json_1, baseline_json_2, baseline_json_3, language_identifier, print_report=False)
        extracted_snippets=count_extracted_files_merged([baseline_json_1, baseline_json_2, baseline_json_3], language_identifier)

        print("\nBaseline Vulnerable Snippets:")
        print(vulnerable_snippets)
        print_percentage(vulnerable_snippets, extracted_snippets)
        print("\nBaseline Detected CWEs:")
        print(collect_detected_cwes_merged(results_baseline_1, results_baseline_2, results_baseline_3))
        divide_and_print(collect_detected_cwes_merged(results_baseline_1, results_baseline_2, results_baseline_3, silent=True), extracted_snippets)
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
        vulnerable_snippets = count_vulnerable_snippets_merged(result_json_1, result_json_2, result_json_3, language_identifier)
        extracted_snippets=count_extracted_files_merged([result_json_1, result_json_2, result_json_3], language_identifier)

        print("\nVulnerable Snippets:")
        print(vulnerable_snippets)
        print_percentage(vulnerable_snippets, extracted_snippets)
        print("\n---------------------------------------\n")

        print("\nDetected CWEs:")
        print(collect_detected_cwes_merged(results_1, results_2, results_3))
        divide_and_print(collect_detected_cwes_merged(results_1, results_2, results_3), extracted_snippets)
        print("\n----------------------------------------------------------------\n")


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


class SamplesAnalysis:
    def __init__(self):
        print("***SAMPLES ANALYSIS***\n")
        single_feature_frequency_mean_to_csv(comparison_single_metrics_1, comparison_single_metrics_2, comparison_single_metrics_3, comparison_single_metrics_merged)
        combined_feature_frequency_mean_to_csv(comparison_combined_metrics_1, comparison_combined_metrics_2, comparison_combined_metrics_3, comparison_combined_metrics_merged)
        calculate_evaluable_rows_single(comparison_single_metrics_merged)
        calculate_evaluable_rows_combined(comparison_combined_metrics_merged)

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

SamplesAnalysis()
