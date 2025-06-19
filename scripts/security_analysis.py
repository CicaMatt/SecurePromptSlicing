import subprocess


def run_sh_commands(commands):
    for command in commands:
        print(f"Running command: {command}")
        try:
            result = subprocess.run(
                command,
                shell=True,
                check=False
            )
            print(f"Command: {command}")
            print(f"Return code: {result.returncode}\n")
        except Exception as e:
            print(f"Command: {command}")
            print(f"Return code: -1")
            print(f"Error: {str(e)}\n")


class SecurityAnalysis:
    def __init__(self, commands):
        run_sh_commands(commands)



example_commands = [
    # C folder cleaning
    r'cd data/prova_c && rm -f *.o vuln _codeql_detected_source_root',
    #r'cd data/prova_c_single && rm -f *.o _codeql_detected_source_root',

    # Databases folder creation (if not exists)
    r'[ -d "CodeQL/Databases" ] || mkdir -p "CodeQL/Databases"',

    # Database creation starting from code
    r'codeql database create CodeQL/Databases/python_example_db --language=python --source-root=data/prova_python --overwrite',
    r'codeql database create CodeQL/Databases/c_example_db --language=c --source-root=data/prova_c --overwrite',
    #r'codeql database create CodeQL/Databases/c_example_db --language=c --source-root=data/prova_c_single --overwrite',
    r'codeql database create CodeQL/Databases/java_example_db --language=java --source-root=data/prova_java --command="mvn clean compile" --overwrite',

    # Query download and installation for C/C++, Python and Java
    r'codeql pack download codeql/python-queries',
    r'codeql pack download codeql/cpp-queries',
    r'codeql pack download codeql/java-queries',

    # Database analysis using downloaded query pack
    r'codeql database analyze CodeQL/Databases/python_example_db --format=csv --output=results_codeql/results_py.csv codeql/python-queries --warnings=hide --rerun',
    r'codeql database analyze CodeQL/Databases/c_example_db --format=csv --output=results_codeql/results_c.csv codeql/cpp-queries --warnings=hide --rerun',
    r'codeql database analyze CodeQL/Databases/java_example_db --format=csv --output=results_codeql/results_java.csv codeql/java-queries --warnings=hide --rerun'
]


command_set_baseline_analysis_py = [
    # Databases folder creation (if not exists)
    r'[ -d "CodeQL/Databases" ] || mkdir -p "CodeQL/Databases"',

    # Database creation starting from code
    r'codeql database create CodeQL/Databases/python_baseline_db --language=python --source-root=baseline_code_py --overwrite',

    # Query update and configuration
    r'cd CodeQL/Queries/py_complete && codeql pack install',

    # Database analysis using downloaded query pack
    r'codeql database analyze CodeQL/Databases/python_baseline_db --format=csv --output=results_codeql/baseline/results_py_baseline.csv codeql/python-queries --warnings=hide --rerun'
    # r'codeql database analyze CodeQL/Databases/python_baseline_db --format=csv --output=results_codeql/results_py.csv CodeQL/Queries/py_complete/python-complete.qls --warnings=hide --rerun'
]


command_set_result_analysis_py = [
    # Databases folder creation (if not exists)
    r'[ -d "CodeQL/Databases" ] || mkdir -p "CodeQL/Databases"',

    # Database creation starting from code
    r'codeql database create CodeQL/Databases/python_analysis_db --language=python --source-root=generated_code_py --overwrite',

    # Query download and installation for C/C++, Python and Java
    r'codeql pack download codeql/python-queries',

    # Database analysis using downloaded query pack
    r'codeql database analyze CodeQL/Databases/python_analysis_db --format=csv --output=results_codeql/permutations/results_py.csv codeql/python-queries --warnings=hide --rerun'
]

"""
command_set_custom_queries_py = [
    # Databases folder creation (if not exists)
    r'[ -d "CodeQL/Databases" ] || mkdir -p "CodeQL/Databases"',

    # Database creation starting from code
    r'codeql database create CodeQL/Databases/python_analysis_db --language=python --source-root=generated_code --overwrite',

    # Query update and configuration
    r'cd CodeQL/Queries/py_complete && codeql pack install',

    # Database analysis using downloaded query pack
    r'codeql database analyze CodeQL/Databases/python_analysis_db --format=csv --output=results_codeql/results_py.csv CodeQL/Queries/py_complete/python-complete.qls --warnings=hide --rerun'
    #r'codeql database analyze CodeQL/Databases/python_analysis_db --format=csv --output=results_codeql/results_py.csv CodeQL/Queries/py_complete_updated/python-complete.qls --warnings=hide --rerun'
    #r'codeql database analyze CodeQL/Databases/python_analysis_db --format=csv --output=results_codeql/results_py.csv CodeQL/Queries/py/top25/python-top25.qls --warnings=hide --rerun'
    #r'codeql database analyze CodeQL/Databases/python_analysis_db --format=csv --output=results_codeql/results_py.csv CodeQL/Queries/py/extra/python-extra.qls --warnings=hide --rerun'
]
"""


command_set_result_analysis_java = [
    # Databases folder creation (if not exists)
    r'[ -d "CodeQL/Databases" ] || mkdir -p "CodeQL/Databases"',

    # Database creation starting from code
    r'codeql database create CodeQL/Databases/java_analysis_db --language=java --source-root=generated_code_java_formatted --command="mvn clean compile --fail-never -e -X" --overwrite',

    # Query download and installation for Java
    r'codeql pack download codeql/java-queries',

    # Database analysis using downloaded query pack
    r'codeql database analyze CodeQL/Databases/java_analysis_db --format=csv --output=results_codeql/permutations/results_java.csv codeql/java-queries --warnings=hide --rerun'
]

# Comandi per testare la compilazione Java
"""
    r'''
    for pom in generated_code_java_formatted/syntactic_permutations_*/code_row_*/pom.xml; do
        dir=$(dirname "$pom")
        echo "🔧 Compilazione in: $dir"
        (cd "$dir" && mvn compile --fail-at-end)
    done
    ''',

        r'''
    for pom in generated_code_java_formatted/syntactic_permutations_*/pom.xml; do
        dir=$(dirname "$pom")
        echo "🔧 Compilazione in: $dir"
        (cd "$dir" && mvn compile --fail-at-end)
    done
    ''',
"""

command_set_result_baseline_c = [
    # Databases folder creation (if not exists)
    r'[ -d "CodeQL/Databases" ] || mkdir -p "CodeQL/Databases"',

    # Database creation starting from code
    r'codeql database create CodeQL/Databases/c_baseline_db --language=c --source-root=generated_code_c --command="../scripts/c_build.sh" --overwrite',

    # Query download and installation for C
    r'codeql pack download codeql/cpp-queries',

    # Database analysis using downloaded query pack
    r'codeql database analyze CodeQL/Databases/c_baseline_db --format=csv --output=results_codeql/baseline/results_c_baseline.csv codeql/cpp-queries --warnings=hide --rerun'
]


command_set_result_analysis_c = [
    # Databases folder creation (if not exists)
    r'[ -d "CodeQL/Databases" ] || mkdir -p "CodeQL/Databases"',

    # Database creation starting from code
    r'codeql database create CodeQL/Databases/c_analysis_db --language=c --source-root=generated_code_c --command="../scripts/c_build.sh" --overwrite',

    # Query download and installation for C
    r'codeql pack download codeql/cpp-queries',

    # Database analysis using downloaded query pack
    r'codeql database analyze CodeQL/Databases/c_analysis_db --format=csv --output=results_codeql/permutations/results_c.csv codeql/cpp-queries --warnings=hide --rerun'
]



#SecurityAnalysis(example_commands)
#SecurityAnalysis(command_set_standard_queries_py)
#SecurityAnalysis(command_set_custom_queries_py)
#SecurityAnalysis(command_set_baseline_analysis_py)
#SecurityAnalysis(command_set_result_analysis_java)
SecurityAnalysis(command_set_result_analysis_c)
