import pandas as pd


def compare_csvs(file1, file2, columns_to_compare=None, key_columns=None, output_csv_path=None):
    def extract_label(filename):
        base = filename.split('_')[-1].split('.')[0]
        return "Python" if base.strip().lower() == "py" else base.capitalize()

    label1 = extract_label(file1)
    label2 = extract_label(file2)

    df1 = pd.read_csv(file1)
    df2 = pd.read_csv(file2)

    if list(df1.columns) != list(df2.columns):
        raise ValueError("I file CSV devono avere le stesse colonne nello stesso ordine.")

    if key_columns is None:
        key_columns = [col for col in ['Value', 'Category'] if col in df1.columns]

    if columns_to_compare is None:
        columns_to_compare = [col for col in df1.columns if col not in key_columns]

    results = []

    for i, (row1, row2) in enumerate(zip(df1.itertuples(index=False), df2.itertuples(index=False))):
        row_dict = {'Row': i}
        key_info = []
        for col in key_columns:
            val = getattr(row1, col, '')
            row_dict[col] = val
            key_info.append(f"{col}: {val}")
        print(" | ".join(key_info))

        for col in columns_to_compare:
            try:
                val1 = getattr(row1, col)
                val2 = getattr(row2, col)

                val1_str = str(val1).strip()
                val2_str = str(val2).strip()
                is_percent = val1_str.endswith('%') or val2_str.endswith('%')

                if is_percent:
                    val1_num = float(val1_str.strip('%')) / 100
                    val2_num = float(val2_str.strip('%')) / 100
                    val1_fmt = f"{val1_num * 100:.2f}%"
                    val2_fmt = f"{val2_num * 100:.2f}%"
                else:
                    val1_num = float(val1)
                    val2_num = float(val2)

                    def fmt(n):
                        return f"{int(n)}" if n == int(n) else f"{n:.2f}"

                    val1_fmt = fmt(val1_num)
                    val2_fmt = fmt(val2_num)

                delta_abs = val2_num - val1_num
                direction = "↑" if delta_abs > 0 else "↓" if delta_abs < 0 else "="

                # Calcolo delta percentuale
                if val1_num == 0:
                    if val2_num == 0:
                        delta_pct = 0.0
                    else:
                        delta_pct = 100.0
                else:
                    delta_pct = (delta_abs / val1_num) * 100

                # Formattazione
                if delta_abs == 0:
                    delta_abs_fmt = f"{delta_abs * 100:.2f}%" if is_percent else "0"
                    delta_pct_fmt = "0.00%"
                else:
                    sign = "+" if delta_abs > 0 else "-"
                    delta_abs_fmt = (
                        f"{sign}{abs(delta_abs) * 100:.2f}%" if is_percent else (
                            f"{sign}{int(abs(delta_abs))}" if abs(delta_abs) == int(abs(delta_abs)) else f"{sign}{abs(delta_abs):.2f}"
                        )
                    )
                    delta_pct_fmt = f"{sign}{abs(delta_pct):.2f}%"

                diff_str = (
                    f"{col:<15} {label1}={val1_fmt:<10} {label2}={val2_fmt:<10} "
                    f"Δ={delta_abs_fmt} ({delta_pct_fmt}) {direction}"
                )
                print("  -", diff_str)

                results.append({
                    **row_dict,
                    'Column': col,
                    f'{label1}': val1_fmt,
                    f'{label2}': val2_fmt,
                    'Delta': delta_abs_fmt,
                    'Delta %': delta_pct_fmt,
                    'Direction': direction,
                })

            except Exception as e:
                print("  -", f"{col:<15} ERRORE confronto: {e}")
                continue

        print()

    if output_csv_path:
        pd.DataFrame(results).to_csv(output_csv_path, index=False)
        print(f"[✔] Confronto salvato su CSV: {output_csv_path}")

    return results


##################################################################################################################

comparison_single_metrics_c = "results/comparison/single_metrics_comparison_c.csv"
comparison_single_metrics_py = "results/comparison/single_metrics_comparison_py.csv"
comparison_single_metrics_java = "results/comparison/single_metrics_comparison_java.csv"

comparison_combined_metrics_c = "results/comparison/combined_metrics_comparison_c.csv"
comparison_combined_metrics_py = "results/comparison/combined_metrics_comparison_py.csv"
comparison_combined_metrics_java = "results/comparison/combined_metrics_comparison_java.csv"

comparison_baseline_cwes_c = "results/comparison/baseline_cwes_comparison_c.csv"
comparison_baseline_cwes_py = "results/comparison/baseline_cwes_comparison_py.csv"
comparison_baseline_cwes_java = "results/comparison/baseline_cwes_comparison_java.csv"

comparison_permutations_cwes_c = "results/comparison/permutations_cwes_comparison_c.csv"
comparison_permutations_cwes_py = "results/comparison/permutations_cwes_comparison_py.csv"
comparison_permutations_cwes_java = "results/comparison/permutations_cwes_comparison_java.csv"


class BaselineCWEsComparison:
    def __init__(self):
        print("Baseline CWE - C/Python:\n")
        compare_csvs(comparison_baseline_cwes_c, comparison_baseline_cwes_py,
                     key_columns=["CWE"], columns_to_compare=["Base", "Result", "Frequency"],
                     output_csv_path="results/cross_comparison/baseline_cwe/baseline_cwe_c_py.csv")
        print("\n---------------------------------------\n")
        print("\nBaseline CWE - C/Java:\n")
        compare_csvs(comparison_baseline_cwes_c, comparison_baseline_cwes_java,
                     key_columns=["CWE"], columns_to_compare=["Base", "Result", "Frequency"],
                     output_csv_path="results/cross_comparison/baseline_cwe/baseline_cwe_c_java.csv")
        print("\n---------------------------------------\n")
        print("\nBaseline CWE - Java/Python:\n")
        compare_csvs(comparison_baseline_cwes_java, comparison_baseline_cwes_py,
                     key_columns=["CWE"], columns_to_compare=["Base", "Result", "Frequency"],
                     output_csv_path="results/cross_comparison/baseline_cwe/baseline_cwe_java_py.csv")
        print("\n----------------------------------------------------------------\n")


class PermutationsCWEsComparison:
    def __init__(self):
        print("Permutations CWE - C/Python:\n")
        compare_csvs(comparison_permutations_cwes_c, comparison_permutations_cwes_py,
                     key_columns=["CWE"], columns_to_compare=["Result", "Frequency"],
                     output_csv_path="results/cross_comparison/permutations_cwe/permutations_cwe_c_py.csv")
        print("\n---------------------------------------\n")
        print("\nPermutations Comparison - C/Java:\n")
        compare_csvs(comparison_permutations_cwes_c, comparison_permutations_cwes_java,
                     key_columns=["CWE"], columns_to_compare=["Result", "Frequency"],
                     output_csv_path="results/cross_comparison/permutations_cwe/permutations_cwe_c_java.csv")
        print("\n---------------------------------------\n")
        print("\nPermutations Comparison - Java/Python:\n")
        compare_csvs(comparison_permutations_cwes_java, comparison_permutations_cwes_py,
                     key_columns=["CWE"], columns_to_compare=["Result", "Frequency"],
                     output_csv_path="results/cross_comparison/permutations_cwe/permutations_cwe_java_py.csv")
        print("\n----------------------------------------------------------------\n")


class SingleMetricsComparison:
    def __init__(self):
        print("***CROSS COMPARISON***\n")
        print("\n---------------------------------------\n")
        print("Single Metrics Comparison - C/Python:\n")
        compare_csvs(comparison_single_metrics_c, comparison_single_metrics_py,
                     key_columns=["Category", "Value"], columns_to_compare=["Result", "Frequency"],
                     output_csv_path="results/cross_comparison/single_metrics/single_metrics_c_py.csv")
        print("\n---------------------------------------\n")
        print("\nSingle Metrics Comparison - C/Java:\n")
        compare_csvs(comparison_single_metrics_c, comparison_single_metrics_java,
                     key_columns=["Category", "Value"], columns_to_compare=["Result", "Frequency"],
                     output_csv_path="results/cross_comparison/single_metrics/single_metrics_c_java.csv")
        print("\n---------------------------------------\n")
        print("\nSingle Metrics Comparison - Java/Python:\n")
        compare_csvs(comparison_single_metrics_java, comparison_single_metrics_py,
                     key_columns=["Category", "Value"], columns_to_compare=["Result", "Frequency"],
                     output_csv_path="results/cross_comparison/single_metrics/single_metrics_java_py.csv")
        print("\n----------------------------------------------------------------\n")


class CombinedMetricsComparison:
    def __init__(self):
        print("Combined Metrics Comparison - C/Python:\n")
        compare_csvs(comparison_combined_metrics_c, comparison_combined_metrics_py,
                     key_columns=["Combination", "Features"], columns_to_compare=["Result", "Frequency"],
                     output_csv_path="results/cross_comparison/combined_metrics/combined_metrics_c_py.csv")
        print("\n---------------------------------------\n")
        print("\nCombined Metrics Comparison - C/Java:\n")
        compare_csvs(comparison_combined_metrics_c, comparison_combined_metrics_java,
                     key_columns=["Combination", "Features"], columns_to_compare=["Result", "Frequency"],
                     output_csv_path="results/cross_comparison/combined_metrics/combined_metrics_c_java.csv")
        print("\n---------------------------------------\n")
        print("\nCombined Metrics Comparison - Java/Python:\n")
        compare_csvs(comparison_combined_metrics_java, comparison_combined_metrics_py,
                     key_columns=["Combination", "Features"], columns_to_compare=["Result", "Frequency"],
                     output_csv_path="results/cross_comparison/combined_metrics/combined_metrics_java_py.csv")
        print("\n----------------------------------------------------------------\n")


BaselineCWEsComparison()
PermutationsCWEsComparison()
SingleMetricsComparison()
CombinedMetricsComparison()
