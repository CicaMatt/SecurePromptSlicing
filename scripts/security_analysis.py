import logging
import os
import re
import shutil
import subprocess
from collections import defaultdict, OrderedDict
from pathlib import Path
from textwrap import dedent

from transformers.trainer_pt_utils import nested_detach


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
    Scansiona ricorsivamente la folder, cerca i file .java,
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



def build_c_project(src_dir, nested=True):
    object_files = []

    if nested:
        # Modalità innestata: cerca sottocartelle in src_dir
        for subdir in next(os.walk(src_dir))[1]:
            sub_src = os.path.join(src_dir, subdir)
            for dirpath, _, filenames in os.walk(sub_src):
                for filename in filenames:
                    if filename.endswith(".c"):
                        src_file = os.path.join(dirpath, filename)
                        rel_path = os.path.relpath(src_file, src_dir)

                        obj_file = os.path.splitext(rel_path)[0] + ".o"
                        object_files.append(obj_file.replace("\\", "/"))
    else:
        # Modalità normale: cerca direttamente i .c in src_dir
        for dirpath, _, filenames in os.walk(src_dir):
            for filename in filenames:
                if filename.endswith(".c"):
                    src_file = os.path.join(dirpath, filename)
                    rel_path = os.path.relpath(src_file, src_dir)

                    obj_file = os.path.splitext(rel_path)[0] + ".o"
                    object_files.append(obj_file.replace("\\", "/"))

    # Genera Makefile direttamente nella src_dir
    makefile_path = os.path.join(src_dir, "Makefile")
    with open(makefile_path, "w") as mf:
        mf.write("CC = gcc\n")
        mf.write("CFLAGS = -Wall -I.\n\n")
        mf.write("all: " + " ".join(object_files) + "\n\n")
        for obj in object_files:
            src = obj.replace(".o", ".c")
            mf.write(f"{obj}: {src}\n\t-$(CC) $(CFLAGS) -c {src} -o {obj}\n\n")
        mf.write("clean:\n\trm -f " + " ".join(object_files) + "\n")



def prepare_directory_for_codeql(source_dir, destination_dir):
    src_path = Path(source_dir).resolve()
    dst_path = Path(destination_dir).resolve()
    stub_dir = dst_path / "__stubs__"

    if dst_path.exists():
        shutil.rmtree(dst_path)
    shutil.copytree(src_path, dst_path)
    stub_dir.mkdir(parents=True, exist_ok=True)

    print(f"[✓] Copiata directory: {src_path} → {dst_path}")

    c_files = list(dst_path.glob("*.c"))

    # Regex
    func_decl = re.compile(r'\b\w[\w\d_]*\s+\**\s*(\w[\w\d_]*)\s*\([^;]*\)\s*\{')
    func_call = re.compile(r'\b(\w[\w\d_]*)\s*\(')
    type_use = re.compile(r'\b([A-Z][A-Za-z0-9_]+)\b')
    type_decl = re.compile(r'typedef\s+struct\s+([A-Za-z_][A-Za-z0-9_]*)')
    field_access = re.compile(r'\b([a-zA-Z_][a-zA-Z0-9_]*)\.([a-zA-Z_][a-zA-Z0-9_]*)')

    STANDARD_FUNCTIONS = {
        "printf", "fprintf", "sprintf", "snprintf", "perror", "puts", "fputs", "fgets", "fgetc", "fputc",
        "malloc", "calloc", "realloc", "free", "exit", "system", "atoi", "atof", "strtol", "rand", "srand",
        "strlen", "strcpy", "strncpy", "strcat", "strcmp", "strncmp", "memcpy", "memset", "memmove",
        "sqrt", "pow", "fabs", "sin", "cos", "tan", "log", "exp",
        "read", "write", "close", "sleep", "usleep", "getpid",
        "time", "difftime", "clock", "strftime",
    }
    STANDARD_TYPES = {
        "FILE", "size_t", "time_t", "clock_t"
    }

    keywords = {"int", "char", "void", "main", "return", "if", "while", "for", "switch", "sizeof"}

    makefile_lines = [
        "CC = gcc",
        "CFLAGS = -Wall -Wextra",
        "",
        "all:"
    ]

    object_files = []

    for cfile in c_files:
        name = cfile.stem
        stub_path = stub_dir / f"{name}_stub.h"
        obj_name = cfile.with_suffix(".o").name
        content = cfile.read_text(encoding="utf-8", errors="ignore")

        # FUNZIONI
        calls = set(func_call.findall(content))
        defs = set(func_decl.findall(content))
        calls = {f for f in calls if f not in defs and f not in STANDARD_FUNCTIONS and f not in keywords}

        # TIPI
        used_types = set(type_use.findall(content))
        defined_types = set(type_decl.findall(content))
        types = {t for t in used_types if t not in defined_types and t not in STANDARD_TYPES and t not in keywords}

        # CAMPI STRUCT
        field_matches = field_access.findall(content)
        struct_fields = defaultdict(set)
        for var, field in field_matches:
            for t in types:
                if var.lower().startswith(t[0].lower()):
                    struct_fields[t].add(field)

        # SKIP file che non usa simboli esterni
        if not calls and not types and "#include <" in content:
            makefile_lines.append(f"\n{obj_name}: {cfile.name}")
            makefile_lines.append(f"\t-$(CC) $(CFLAGS) -c {cfile.name} -o {obj_name}")
            continue

        # COSTRUISCI HEADER
        guard = f"{name.upper()}_STUB_H"
        lines = [f"#ifndef {guard}", f"#define {guard}", ""]

        for t in sorted(types):
            fields = struct_fields.get(t)
            if fields:
                lines.append(f"typedef struct {t} {{")
                for f in sorted(fields):
                    lines.append(f"    int {f};")
                lines.append(f"}} {t};")
            else:
                lines.append(f"typedef struct {t} {t};")

        lines.append("")
        for f in sorted(calls):
            lines.append(f"int {f}();")
        lines.append("\n#endif")

        stub_path.write_text("\n".join(lines))

        # MAKEFILE
        makefile_lines.append(f"\n{obj_name}: {cfile.name}")
        makefile_lines.append(f"\t-$(CC) $(CFLAGS) -I__stubs__ -include __stubs__/{name}_stub.h -c {cfile.name} -o {obj_name}")
        object_files.append(obj_name)

    makefile_lines.append("\nall: " + " ".join(object_files))
    (dst_path / "Makefile").write_text("\n".join(makefile_lines))

    print(f"[✓] Stub generati solo dove servono")
    print(f"[✓] Makefile pronto con {len(object_files)} file")
    print(f"[✓] Directory finale pronta in: {dst_path}")


def prepara_progetto_c(cartella_input, cartella_output, nome_eseguibile):
    """
    Orchestra l'intero processo di preparazione di un progetto C.

    1.  Copia la folder sorgente in una nuova folder di build.
    2.  Analizza i file .c per generare i corrispondenti file header .h.
    3.  Crea un Makefile completo per la compilazione.

    Args:
        cartella_input (str): Percorso della folder contenente i sorgenti .c.
        cartella_output (str): Percorso della folder di build da creare.
        nome_eseguibile (str): Nome del programma finale da compilare.
    """

    # --- Funzioni ausiliarie interne ---

    def estrai_prototipi_funzioni(contenuto_file_c):
        """Estrae i prototipi di funzione da una stringa di codice C."""
        regex_funzione = re.compile(
            r"^\s*(?!static\b)([\w\s\*&]+?)\s+([\w_]+)\s*\(([^)]*)\)\s*\{",
            re.MULTILINE
        )
        prototipi = []
        for match in regex_funzione.finditer(contenuto_file_c):
            tipo_ritorno = match.group(1).strip()
            nome_funzione = match.group(2).strip()
            argomenti = match.group(3).strip()
            argomenti_puliti = re.sub(r'\s+', ' ', argomenti)
            prototipo = f"{tipo_ritorno} {nome_funzione}({argomenti_puliti});"
            prototipi.append(prototipo)
        return prototipi

    def crea_makefile():
        """Crea un Makefile nella folder di output."""
        percorso_makefile = os.path.join(cartella_output, "Makefile")
        elenco_file_c = [f for f in os.listdir(cartella_output) if f.endswith(".c")]
        if not elenco_file_c:
            logging.warning("Nessun file .c trovato, Makefile non creato.")
            return

        contenuto_makefile = f"""# Makefile generato automaticamente
CC = gcc
CFLAGS = -Wall -Wextra -g -I.
TARGET = {nome_eseguibile}
SRCS = $(wildcard *.c)
OBJS = $(SRCS:.c=.o)

.PHONY: all clean re

all: $(TARGET)

$(TARGET): $(OBJS)
	@echo "Linking..."
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)
	@echo "Build completato! Eseguibile '{nome_eseguibile}' creato."

%.o: %.c
	@echo "Compiling $<..."
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	@echo "Cleaning build files..."
	rm -f $(OBJS) $(TARGET)

re: clean all
"""
        try:
            with open(percorso_makefile, 'w', encoding='utf-8') as f:
                f.write(contenuto_makefile)
            logging.info(f"Makefile creato con successo in '{percorso_makefile}'")
        except IOError as e:
            logging.error(f"Impossibile scrivere il Makefile: {e}")

    # --- Logica principale della funzione ---

    # 1. Preparazione della folder di build
    if not os.path.isdir(cartella_input):
        logging.error(f"La folder di input '{cartella_input}' non esiste.")
        return False

    if os.path.exists(cartella_output):
        logging.info(f"Rimuovo la vecchia folder di build '{cartella_output}'.")
        shutil.rmtree(cartella_output)

    try:
        shutil.copytree(cartella_input, cartella_output)
        logging.info(f"Copia dei sorgenti da '{cartella_input}' a '{cartella_output}' completata.")
    except OSError as e:
        logging.error(f"Errore durante la copia dei file: {e}")
        return False

    # 2. Generazione dei file Header
    logging.info(f"Avvio analisi e creazione degli header in '{cartella_output}'.")
    for nome_file in os.listdir(cartella_output):
        if nome_file.endswith(".c"):
            percorso_file_c = os.path.join(cartella_output, nome_file)
            nome_base = os.path.splitext(nome_file)[0]
            percorso_file_h = os.path.join(cartella_output, f"{nome_base}.h")

            if os.path.exists(percorso_file_h):
                logging.warning(f"Header '{nome_base}.h' già presente, non verrà modificato.")
                continue

            try:
                with open(percorso_file_c, 'r', encoding='utf-8') as f:
                    contenuto = f.read()
            except IOError as e:
                logging.error(f"Impossibile leggere il file '{nome_file}': {e}")
                continue

            prototipi = estrai_prototipi_funzioni(contenuto)
            if not prototipi:
                logging.info(f"Nessuna funzione pubblica in '{nome_file}', header non generato.")
                continue

            try:
                with open(percorso_file_h, 'w', encoding='utf-8') as f_header:
                    nome_guardia = f"{nome_base.upper()}_H"
                    f_header.write(f"/* File header generato automaticamente per {nome_file} */\n\n")
                    f_header.write(f"#ifndef {nome_guardia}\n#define {nome_guardia}\n\n")
                    f_header.write("\n".join(prototipi))
                    f_header.write(f"\n\n#endif /* {nome_guardia} */\n")
                logging.info(f"Creato file '{nome_base}.h'.")
            except IOError as e:
                logging.error(f"Impossibile scrivere il file '{nome_base}.h': {e}")

    # 3. Creazione del Makefile
    crea_makefile()

    print(f"\nOperazione completata. La folder di build '{cartella_output}' è pronta.")
    print("Per compilare, esegui i seguenti comandi:")
    print(f"  cd {cartella_output}")
    print("  make")

    return True


def add_missing_includes(root_dir, standard_c_functions):
    # Ottiene la lista degli header dalla struttura standard_c_functions
    standard_headers = list(standard_c_functions.keys())

    for dirpath, _, filenames in os.walk(root_dir):
        for file in filenames:
            if file.endswith(".c"):
                filepath = os.path.join(dirpath, file)
                with open(filepath, 'r', encoding='utf-8') as f:
                    content = f.read()

                # Trova tutti gli include già presenti
                included_headers = set(re.findall(r'#include\s+<([^>]+)>', content))

                # Determina quali header mancano
                missing_headers = [h for h in standard_headers if h not in included_headers]

                if missing_headers:
                    # Crea le nuove righe da aggiungere
                    new_includes = '\n'.join(f'#include <{header}>' for header in missing_headers)

                    # Inserisci gli include all'inizio del file
                    new_content = new_includes + '\n\n' + content

                    # Sovrascrive il file con gli include aggiornati
                    with open(filepath, 'w', encoding='utf-8') as f:
                        f.write(new_content)

                    print(f"Aggiunti {len(missing_headers)} include a: {filepath}")
                else:
                    print(f"Nessun include mancante in: {filepath}")


###################################################################################################################


class SecurityAnalysis:
    def __init__(self, commands):
        run_sh_commands(commands)


class JavaPreprocessing:
    def __init__(self, folder1, folder2, nested):
        self.folder1 = folder1
        self.folder2 = folder2
        self.nested = nested
        # Struttura la folder con i vari pom.xml per ogni singolo file, per ogni gruppo di permutazioni e per tutta la folder
        organize_java_snippets(folder1, folder2, nested)
        # Scansiona ricorsivamente i file .java, estrae il nome della prima classe e rinomina il file di conseguenza evitando nomi duplicati (incapsula anche codici vuoti in classi wrapper)
        process_java_files(folder2)
        #find_errors_java(folder2)


class CPreprocessing:
    def __init__(self, folder1, folder2, nested):
        self.folder1 = folder1
        self.folder2 = folder2
        self.nested = nested

        STANDARD_C_FUNCTIONS = {
            "assert.h": {"assert"},
            "ctype.h": {
                "isalnum", "isalpha", "isascii", "iscntrl", "isdigit", "isgraph",
                "islower", "isprint", "ispunct", "isspace", "isupper", "isxdigit",
                "tolower", "toupper"
            },
            "errno.h": {"errno"},
            "float.h": set(),  # solo macro/costanti
            "limits.h": set(),  # solo macro/costanti
            "locale.h": {"setlocale", "localeconv"},
            "math.h": {
                "acos", "asin", "atan", "atan2", "cos", "sin", "tan", "cosh", "sinh", "tanh",
                "exp", "frexp", "ldexp", "log", "log10", "modf", "pow", "sqrt", "ceil",
                "fabs", "floor", "fmod", "isnan", "isinf", "isfinite"
            },
            "setjmp.h": {"setjmp", "longjmp"},
            "signal.h": {"signal", "raise"},
            "stdarg.h": {"va_start", "va_arg", "va_end", "va_copy"},
            "stddef.h": set(),  # solo macro/tipi
            "stdio.h": {
                "printf", "fprintf", "sprintf", "snprintf", "scanf", "fscanf", "sscanf",
                "vprintf", "vfprintf", "vsprintf", "fopen", "fclose", "fflush", "fgetc",
                "fgets", "fputc", "fputs", "fread", "fwrite", "fseek", "ftell", "rewind",
                "feof", "ferror", "clearerr", "perror", "getchar", "putchar", "gets",
                "puts", "remove", "rename", "tmpfile", "tmpnam", "setbuf", "setvbuf"
            },
            "stdlib.h": {
                "malloc", "calloc", "realloc", "free", "abort", "exit", "atexit",
                "system", "getenv", "atoi", "atol", "atof", "strtod", "strtol", "strtoul",
                "rand", "srand", "bsearch", "qsort", "abs", "labs", "div", "ldiv"
            },
            "string.h": {
                "memcpy", "memmove", "strcpy", "strncpy", "strcat", "strncat",
                "memcmp", "strcmp", "strncmp", "strcoll", "strxfrm", "memchr", "strchr",
                "strcspn", "strpbrk", "strrchr", "strspn", "strstr", "strtok", "strlen",
                "strerror"
            },
            "time.h": {
                "clock", "time", "difftime", "mktime", "asctime", "ctime",
                "gmtime", "localtime", "strftime"
            },
            "complex.h": {
                "cabs", "cacos", "cacosh", "carg", "casin", "casinh", "catan",
                "catanh", "ccos", "ccosh", "cexp", "cimag", "clog", "conj",
                "cpow", "cproj", "creal", "csin", "csinh", "csqrt", "ctan", "ctanh"
            },
            "fenv.h": {
                "feclearexcept", "fegetexceptflag", "feraiseexcept", "fesetexceptflag",
                "fetestexcept", "fegetround", "fesetround", "fegetenv", "fesetenv"
            },
            "inttypes.h": {
                "imaxabs", "imaxdiv", "strtoimax", "strtoumax", "wcstoimax", "wcstoumax"
            },
            "stdbool.h": set(),  # solo macro/tipi (true, false, bool)
            "stdint.h": set(),  # solo tipi (int32_t ecc.)
            "tgmath.h": set(),  # macro generiche (non funzioni reali)
            "stdalign.h": set(),  # macro (_Alignof ecc.)
            "stdatomic.h": set(),  # macro e tipi per operazioni atomiche
            "stdnoreturn.h": set(),  # solo macro (_Noreturn)
        }

        if os.path.exists(folder2):
            shutil.rmtree(folder2)

        # Copia ricorsiva della cartella sorgente nella destinazione
        shutil.copytree(folder1, folder2)

        add_missing_includes(folder2, STANDARD_C_FUNCTIONS)
        build_c_project(folder2, nested)

        # GARBAGE
        #prepare_directory_for_codeql(folder1, folder2)
        #prepara_progetto_c(folder1, folder2, "make")



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
    r'codeql database create CodeQL/Databases/c_baseline_db --language=c --source-root=generated_code/baseline_code_c_formatted --command="make -k" --overwrite',

    # Query download and installation for C
    r'codeql pack download codeql/cpp-queries',

    # Database analysis using downloaded query pack
    r'codeql database analyze CodeQL/Databases/c_baseline_db --format=csv --output=results/baseline/results_c_baseline.csv codeql/cpp-queries --warnings=hide --rerun'
]


command_set_result_analysis_c = [
    # Databases folder creation (if not exists)
    r'[ -d "CodeQL/Databases" ] || mkdir -p "CodeQL/Databases"',

    # Database creation starting from code
    r'codeql database create CodeQL/Databases/c_analysis_db --language=c --source-root=generated_code/generated_code_c_formatted --command="make -k" --overwrite',

    # Query download and installation for C
    r'codeql pack download codeql/cpp-queries',

    # Database analysis using downloaded query pack
    r'codeql database analyze CodeQL/Databases/c_analysis_db --format=csv --output=results/permutations/results_c.csv codeql/cpp-queries --warnings=hide --rerun'
]


java_baseline_folder = "generated_code/baseline_code_java"
java_baseline_folder_formatted = "generated_code/baseline_code_java_formatted"
java_folder = "generated_code/generated_code_java"
java_folder_formatted = "generated_code/generated_code_java_formatted"

c_baseline_folder = "generated_code/baseline_code_c"
c_baseline_folder_formatted = "generated_code/baseline_code_c_formatted"
c_folder = "generated_code/generated_code_c"
c_folder_formatted = "generated_code/generated_code_c_formatted"


#SecurityAnalysis(example_commands)
#SecurityAnalysis(command_set_custom_queries_py)




#SecurityAnalysis(command_set_baseline_analysis_py)
#SecurityAnalysis(command_set_result_analysis_py)

JavaPreprocessing(java_baseline_folder, java_baseline_folder_formatted, nested=False)
SecurityAnalysis(command_set_baseline_analysis_java)
#JavaPreprocessing(java_folder, java_folder_formatted, nested=True)
#SecurityAnalysis(command_set_result_analysis_java)

#CPreprocessing(c_baseline_folder, c_baseline_folder_formatted, nested=False)
#SecurityAnalysis(command_set_baseline_analysis_c)
#CPreprocessing(c_folder, c_folder_formatted, nested=True)
#SecurityAnalysis(command_set_result_analysis_c)
