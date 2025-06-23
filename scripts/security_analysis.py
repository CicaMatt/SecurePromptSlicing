import os
import re
import shutil
import subprocess
from collections import defaultdict
from pathlib import Path


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



def organize_java_snippets(code_path: str = None, output_path: str = None, nested: bool = True):
    if code_path is None:
        code_path = Path.cwd()
    else:
        code_path = Path(code_path)

    if output_path is None:
        raise ValueError("È necessario specificare un 'output_path'.")
    output_path = Path(output_path)

    if output_path.exists() and output_path.is_dir():
        shutil.rmtree(output_path)
    output_path.mkdir(parents=True, exist_ok=True)

    aggregators_created = set()
    java_files = list(code_path.rglob("*.java") if nested else code_path.glob("*.java"))

    for java_file in java_files:
        relative_path = java_file.relative_to(code_path).parent if nested else Path()
        basename = java_file.stem

        module_name = f"{relative_path.as_posix().replace('/', '-')}-{basename}" if nested and relative_path.parts else basename

        new_dir = output_path / relative_path / basename if nested else output_path / basename
        dest_dir = new_dir / "src/main/java"
        dest_dir.mkdir(parents=True, exist_ok=True)

        print(f"Elaboro: {java_file} -> {dest_dir}")
        shutil.copy2(java_file, dest_dir / java_file.name)

        parent_artifact_id = (
            'aggregator-root' if not nested else new_dir.parent.name + '-parent'
        )

        module_pom = new_dir / "pom.xml"
        module_pom.write_text(f'''<project xmlns="http://maven.apache.org/POM/4.0.0"
         xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
         xsi:schemaLocation="http://maven.apache.org/POM/4.0.0 
                             http://maven.apache.org/xsd/maven-4.0.0.xsd">
  <modelVersion>4.0.0</modelVersion>
  <parent>
    <groupId>com.example</groupId>
    <artifactId>{parent_artifact_id}</artifactId>
    <version>1.0.0</version>
    <relativePath>../pom.xml</relativePath>
  </parent>
  <artifactId>{module_name}</artifactId>

  <build>
    <plugins>
      <plugin>
        <groupId>org.apache.maven.plugins</groupId>
        <artifactId>maven-compiler-plugin</artifactId>
        <version>3.10.1</version>
        <configuration>
          <source>11</source>
          <target>11</target>
        </configuration>
      </plugin>
    </plugins>
  </build>
</project>''')

        if nested:
            aggregator_dir = new_dir.parent
            aggregator_pom = aggregator_dir / "pom.xml"
            if aggregator_dir not in aggregators_created:
                aggregator_artifact_id = f"{aggregator_dir.name}-parent"
                aggregator_pom.write_text(f'''<project xmlns="http://maven.apache.org/POM/4.0.0"
         xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
         xsi:schemaLocation="http://maven.apache.org/POM/4.0.0 
                             http://maven.apache.org/xsd/maven-4.0.0.xsd">
  <modelVersion>4.0.0</modelVersion>
  <groupId>com.example</groupId>
  <artifactId>{aggregator_artifact_id}</artifactId>
  <version>1.0.0</version>
  <packaging>pom</packaging>
  <modules>
    <module>{basename}</module>
  </modules>
</project>''')
                aggregators_created.add(aggregator_dir)
            else:
                text = aggregator_pom.read_text()
                if f"<module>{basename}</module>" not in text:
                    text = text.replace("</modules>", f"    <module>{basename}</module>\n  </modules>")
                    aggregator_pom.write_text(text)
        else:
            aggregators_created.add(new_dir)

    # CREA POM AGGREGATORE GLOBALE
    if nested:
        global_modules = [
            str(p.relative_to(output_path))
            for p in aggregators_created
        ]
    else:
        global_modules = sorted([
            d.name
            for d in output_path.iterdir()
            if d.is_dir() and (d / "pom.xml").exists()
        ])

    global_pom_content = f'''<project xmlns="http://maven.apache.org/POM/4.0.0"
     xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
     xsi:schemaLocation="http://maven.apache.org/POM/4.0.0 
                         http://maven.apache.org/xsd/maven-4.0.0.xsd">
  <modelVersion>4.0.0</modelVersion>
  <groupId>com.example</groupId>
  <artifactId>aggregator-root</artifactId>
  <version>1.0.0</version>
  <packaging>pom</packaging>
  <modules>
'''

    for module_path in global_modules:
        global_pom_content += f"    <module>{module_path}</module>\n"

    global_pom_content += '''  </modules>
</project>'''

    (output_path / "pom.xml").write_text(global_pom_content)


def process_java_files(folder, wrap_if_no_class=True):
    """
    Scansiona ricorsivamente la cartella, cerca i file .java,
    estrae il nome della prima classe e rinomina il file di conseguenza,
    evitando nomi duplicati.

    Se `wrap_if_no_class` è True e non viene trovata alcuna classe,
    incapsula il contenuto in una classe generica.
    """
    used_class_names = set()

    for root, _, files in os.walk(folder):
        for filename in files:
            if filename.endswith(".java"):
                complete_path = os.path.join(root, filename)
                with open(complete_path, 'r', encoding='utf-8', errors='ignore') as f:
                    content = f.read()

                match = re.search(r'\bclass\s+(\w+)', content)
                if match:
                    original_class_name = match.group(1)
                elif wrap_if_no_class:
                    # Genera nome classe generica da nome file
                    original_class_name = os.path.splitext(filename)[0].capitalize() + "Wrapper"
                    content = f"public class {original_class_name} {{\n{content}\n}}"
                    with open(complete_path, 'w', encoding='utf-8') as f:
                        f.write(content)
                    print(f"Nessuna classe trovata in: {filename}, incapsulato in classe {original_class_name}.")
                else:
                    print(f"Saltato: {filename} (nessuna classe trovata e wrapping disabilitato).")
                    continue  # Salta il file

                # Evita nomi duplicati
                class_name = original_class_name
                counter = 1
                while class_name in used_class_names:
                    class_name = f"{original_class_name}_{counter}"
                    counter += 1

                used_class_names.add(class_name)

                # Se il nome è stato modificato, aggiorna anche il contenuto della classe
                if class_name != original_class_name:
                    content = re.sub(r'\bclass\s+' + re.escape(original_class_name), f'class {class_name}', content)
                    with open(complete_path, 'w', encoding='utf-8') as f:
                        f.write(content)
                    print(f"Classe {original_class_name} rinominata in {class_name} per evitare duplicati.")

                new_name = class_name + ".java"
                new_path = os.path.join(root, new_name)
                if new_path != complete_path:
                    print(f"Rinomino: {filename} -> {new_name}")
                    os.rename(complete_path, new_path)


def duplication_removal(base_dir):
    class_name_counts = defaultdict(int)
    renamed_classes = {}

    # Step 1: raccogli tutte le classi (anche non pubbliche)
    java_files = []
    class_pattern = re.compile(r'\b(class|interface|enum)\s+(\w+)')

    for root, _, files in os.walk(base_dir):
        for file in files:
            if file.endswith(".java"):
                full_path = os.path.join(root, file)
                java_files.append(full_path)

    for path in java_files:
        with open(path, 'r', encoding='utf-8') as f:
            content = f.read()

        for match in class_pattern.finditer(content):
            class_name = match.group(2)
            class_name_counts[class_name] += 1

    # Step 2: rinomina classi duplicate
    for path in java_files:
        with open(path, 'r', encoding='utf-8') as f:
            content = f.read()

        modified = False
        new_content = content

        for match in class_pattern.finditer(content):
            keyword, old_name = match.groups()
            if class_name_counts[old_name] > 1:
                base = old_name
                i = 1
                while True:
                    new_name = f"{base}_{i}"
                    if new_name not in class_name_counts:
                        break
                    i += 1

                new_content = re.sub(rf'\b{keyword}\s+{old_name}\b',
                                     f'{keyword} {new_name}', new_content)
                class_name_counts[new_name] = 1
                renamed_classes[old_name] = new_name
                modified = True

                # rinomina anche il file se il nome file coincide con la classe
                file_name = os.path.basename(path)
                if file_name == f"{old_name}.java":
                    new_file_name = os.path.join(os.path.dirname(path), f"{new_name}.java")
                    os.rename(path, new_file_name)
                    path = new_file_name  # aggiorna per evitare future collisioni
                    break

        if modified:
            with open(path, 'w', encoding='utf-8') as f:
                f.write(new_content)

    return renamed_classes


def find_errors_java(folder):
    errors = {}

    for root, _, files in os.walk(folder):
        for file in files:
            if file.endswith(".java"):
                filepath = os.path.join(root, file)
                try:
                    result = subprocess.run(
                        ["javac", filepath],
                        capture_output=True,
                        text=True
                    )
                    if result.returncode != 0:
                        errors[filepath] = result.stderr.strip()
                except FileNotFoundError:
                    print("Errore: javac non trovato. Assicurati che Java sia installato e presente nel PATH.")
                    return None

    if errors:
        print("\n=== File con errors sintattici ===")
        for idx, (file, message) in enumerate(sorted(errors.items()), start=1):
            print(f"{idx}. {file}")
            print(f"   → Errore: {message.splitlines()[0]}\n")  # stampa solo la prima riga dell'errore

        print(f"Totale file non validi: {len(errors)}")
    else:
        print("Tutti i file .java sono sintatticamente corretti.")

    return errors


###################################################################################################################


class SecurityAnalysis:
    def __init__(self, commands):
        run_sh_commands(commands)


class JavaPreprocessing:
    def __init__(self, folder1, folder2, nested):
        self.folder1 = folder1
        self.folder2 = folder2
        self.nested = nested
        # Struttura la cartella con i vari pom.xml per ogni singolo file, per ogni gruppo di permutazioni e per tutta la folder
        organize_java_snippets(folder1, folder2, nested)
        # Scansiona ricorsivamente i file .java, estrae il nome della prima classe e rinomina il file di conseguenza evitando nomi duplicati (incapsula anche codici vuoti in classi wrapper)
        process_java_files(folder2)
        #find_errors_java(folder2)


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
    r'codeql database analyze CodeQL/Databases/python_example_db --format=csv --output=results/results_py.csv codeql/python-queries --warnings=hide --rerun',
    r'codeql database analyze CodeQL/Databases/c_example_db --format=csv --output=results/results_c.csv codeql/cpp-queries --warnings=hide --rerun',
    r'codeql database analyze CodeQL/Databases/java_example_db --format=csv --output=results/results_java.csv codeql/java-queries --warnings=hide --rerun'
]


command_set_baseline_analysis_py = [
    # Databases folder creation (if not exists)
    r'[ -d "CodeQL/Databases" ] || mkdir -p "CodeQL/Databases"',

    # Database creation starting from code
    r'codeql database create CodeQL/Databases/python_baseline_db --language=python --source-root=generated_code/baseline_code_py --overwrite',

    # Query update and configuration
    r'cd CodeQL/Queries/py_complete && codeql pack install',

    # Database analysis using downloaded query pack
    r'codeql database analyze CodeQL/Databases/python_baseline_db --format=csv --output=results/baseline/results_py_baseline.csv codeql/python-queries --warnings=hide --rerun'
    # r'codeql database analyze CodeQL/Databases/python_baseline_db --format=csv --output=results/results_py.csv CodeQL/Queries/py_complete/python-complete.qls --warnings=hide --rerun'
]


command_set_result_analysis_py = [
    # Databases folder creation (if not exists)
    r'[ -d "CodeQL/Databases" ] || mkdir -p "CodeQL/Databases"',

    # Database creation starting from code
    r'codeql database create CodeQL/Databases/python_analysis_db --language=python --source-root=generated_code/generated_code_py --overwrite',

    # Query download and installation for C/C++, Python and Java
    r'codeql pack download codeql/python-queries',

    # Database analysis using downloaded query pack
    r'codeql database analyze CodeQL/Databases/python_analysis_db --format=csv --output=results/permutations/results_py.csv codeql/python-queries --warnings=hide --rerun'
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
    r'codeql database analyze CodeQL/Databases/python_analysis_db --format=csv --output=results/results_py.csv CodeQL/Queries/py_complete/python-complete.qls --warnings=hide --rerun'
    #r'codeql database analyze CodeQL/Databases/python_analysis_db --format=csv --output=results/results_py.csv CodeQL/Queries/py_complete_updated/python-complete.qls --warnings=hide --rerun'
    #r'codeql database analyze CodeQL/Databases/python_analysis_db --format=csv --output=results/results_py.csv CodeQL/Queries/py/top25/python-top25.qls --warnings=hide --rerun'
    #r'codeql database analyze CodeQL/Databases/python_analysis_db --format=csv --output=results/results_py.csv CodeQL/Queries/py/extra/python-extra.qls --warnings=hide --rerun'
]
"""


command_set_baseline_analysis_java = [
    # Databases folder creation (if not exists)
    r'[ -d "CodeQL/Databases" ] || mkdir -p "CodeQL/Databases"',

    # Database creation starting from code
    r'codeql database create CodeQL/Databases/java_baseline_db --language=java --source-root=generated_code/baseline_code_java_formatted --command="mvn clean compile --fail-never -e -X" --overwrite',

    # Query download and installation for Java
    r'codeql pack download codeql/java-queries',

    # Database analysis using downloaded query pack
    r'codeql database analyze CodeQL/Databases/java_baseline_db --format=csv --output=results/baseline/results_java_baseline.csv codeql/java-queries --warnings=hide --rerun'
]


command_set_result_analysis_java = [
    # Databases folder creation (if not exists)
    r'[ -d "CodeQL/Databases" ] || mkdir -p "CodeQL/Databases"',

    # Database creation starting from code
    r'codeql database create CodeQL/Databases/java_analysis_db --language=java --source-root=generated_code/generated_code_java_formatted --command="mvn clean compile --fail-never -e -X" --overwrite',

    # Query download and installation for Java
    r'codeql pack download codeql/java-queries',

    # Database analysis using downloaded query pack
    r'codeql database analyze CodeQL/Databases/java_analysis_db --format=csv --output=results/permutations/results_java.csv codeql/java-queries --warnings=hide --rerun'
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

command_set_baseline_analysis_c = [
    # Databases folder creation (if not exists)
    r'[ -d "CodeQL/Databases" ] || mkdir -p "CodeQL/Databases"',

    # Database creation starting from code
    r'codeql database create CodeQL/Databases/c_baseline_db --language=c --source-root=generated_code/baseline_code_c --command="../../scripts/c_build.sh" --overwrite',

    # Query download and installation for C
    r'codeql pack download codeql/cpp-queries',

    # Database analysis using downloaded query pack
    r'codeql database analyze CodeQL/Databases/c_baseline_db --format=csv --output=results/baseline/results_c_baseline.csv codeql/cpp-queries --warnings=hide --rerun'
]


command_set_result_analysis_c = [
    # Databases folder creation (if not exists)
    r'[ -d "CodeQL/Databases" ] || mkdir -p "CodeQL/Databases"',

    # Database creation starting from code
    r'codeql database create CodeQL/Databases/c_analysis_db --language=c --source-root=generated_code/generated_code_c --command="../../scripts/c_build.sh" --overwrite',

    # Query download and installation for C
    r'codeql pack download codeql/cpp-queries',

    # Database analysis using downloaded query pack
    r'codeql database analyze CodeQL/Databases/c_analysis_db --format=csv --output=results/permutations/results_c.csv codeql/cpp-queries --warnings=hide --rerun'
]

java_baseline_folder = "generated_code/baseline_code_java"
java_baseline_folder_formatted = "generated_code/baseline_code_java_formatted"
java_folder = "generated_code/generated_code_java"
java_folder_formatted = "generated_code/generated_code_java_formatted"



#SecurityAnalysis(example_commands)
#SecurityAnalysis(command_set_custom_queries_py)

#SecurityAnalysis(command_set_baseline_analysis_py)
#SecurityAnalysis(command_set_result_analysis_py)

#JavaPreprocessing(java_baseline_folder, java_baseline_folder_formatted, nested=False)
#SecurityAnalysis(command_set_baseline_analysis_java)
JavaPreprocessing(java_folder, java_folder_formatted, nested=True)
SecurityAnalysis(command_set_result_analysis_java)

#SecurityAnalysis(command_set_baseline_analysis_c)
#SecurityAnalysis(command_set_result_analysis_c)
