import json
import logging
import os
import re
import shutil
import subprocess
from collections import defaultdict, OrderedDict
from pathlib import Path
from textwrap import dedent

import pandas as pd
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


def wrap_inside_class(folder):
    """
    Cerca file .java nella cartella (ricorsivamente).
    Se un file non ha una classe, incapsula il contenuto in una classe.
    """
    for root, _, files in os.walk(folder):
        for filename in files:
            if filename.endswith(".java"):
                full_path = os.path.join(root, filename)
                with open(full_path, 'r', encoding='utf-8', errors='ignore') as f:
                    content = f.read()

                if not re.search(r'\bclass\s+\w+', content):
                    class_name = os.path.splitext(filename)[0].capitalize() + "Wrapper"
                    wrapped = f"public class {class_name} {{\n{content}\n}}"
                    with open(full_path, 'w', encoding='utf-8') as f:
                        f.write(wrapped)
                    print(f"Wrapped {filename} in class {class_name}")



def create_maven_structure(code_path: str, nested: bool = False, with_imports: bool = False):
    code_path = Path(code_path)
    aggregators_created = set()

    # Blocco XML con tutte le dipendenze richieste
    external_dependencies_xml = '''
<dependencies>
  <!-- GSON -->
  <dependency>
    <groupId>com.google.code.gson</groupId>
    <artifactId>gson</artifactId>
    <version>2.10.1</version>
  </dependency>

  <!-- Unirest -->
  <dependency>
    <groupId>com.konghq</groupId>
    <artifactId>unirest-java</artifactId>
    <version>3.13.6</version>
  </dependency>

  <!-- MySQL -->
  <dependency>
    <groupId>mysql</groupId>
    <artifactId>mysql-connector-java</artifactId>
    <version>8.0.33</version>
  </dependency>

  <!-- Commons Codec -->
  <dependency>
    <groupId>commons-codec</groupId>
    <artifactId>commons-codec</artifactId>
    <version>1.16.0</version>
  </dependency>

  <!-- Commons Compress -->
  <dependency>
    <groupId>org.apache.commons</groupId>
    <artifactId>commons-compress</artifactId>
    <version>1.25.0</version>
  </dependency>

  <!-- Commons FileUpload -->
  <dependency>
    <groupId>commons-fileupload</groupId>
    <artifactId>commons-fileupload</artifactId>
    <version>1.5</version>
  </dependency>

  <!-- Commons IO -->
  <dependency>
    <groupId>commons-io</groupId>
    <artifactId>commons-io</artifactId>
    <version>2.15.1</version>
  </dependency>

  <!-- Apache HttpClient -->
  <dependency>
    <groupId>org.apache.httpcomponents</groupId>
    <artifactId>httpclient</artifactId>
    <version>4.5.14</version>
  </dependency>

  <!-- Spring Boot Web -->
  <dependency>
    <groupId>org.springframework.boot</groupId>
    <artifactId>spring-boot-starter-web</artifactId>
    <version>3.2.4</version>
  </dependency>

  <!-- Spring Boot Thymeleaf -->
  <dependency>
    <groupId>org.springframework.boot</groupId>
    <artifactId>spring-boot-starter-thymeleaf</artifactId>
    <version>3.2.4</version>
  </dependency>

  <!-- SnakeYAML -->
  <dependency>
    <groupId>org.yaml</groupId>
    <artifactId>snakeyaml</artifactId>
    <version>2.4</version>
  </dependency>

  <!-- SparkJava -->
  <dependency>
    <groupId>com.sparkjava</groupId>
    <artifactId>spark-core</artifactId>
    <version>2.9.4</version>
  </dependency>

  <dependency>
    <groupId>com.sparkjava</groupId>
    <artifactId>spark-template-freemarker</artifactId>
    <version>2.7.1</version>
  </dependency>

  <!-- Auth0 JWT -->
  <dependency>
    <groupId>com.auth0</groupId>
    <artifactId>java-jwt</artifactId>
    <version>4.4.0</version>
  </dependency>

  <!-- Jackson (per JSON/YAML) -->
  <dependency>
    <groupId>com.fasterxml.jackson.core</groupId>
    <artifactId>jackson-databind</artifactId>
    <version>2.17.1</version>
  </dependency>
  <dependency>
    <groupId>com.fasterxml.jackson.dataformat</groupId>
    <artifactId>jackson-dataformat-yaml</artifactId>
    <version>2.17.1</version>
  </dependency>

  <!-- Javalin -->
  <dependency>
    <groupId>io.javalin</groupId>
    <artifactId>javalin</artifactId>
    <version>5.6.3</version>
  </dependency>

  <!-- Java Servlet API (per HttpServletRequest/Response) -->
  <dependency>
    <groupId>jakarta.servlet</groupId>
    <artifactId>jakarta.servlet-api</artifactId>
    <version>6.0.0</version>
    <scope>provided</scope>
  </dependency>

  <!-- iText PDF -->
  <dependency>
    <groupId>com.itextpdf</groupId>
    <artifactId>itextpdf</artifactId>
    <version>5.5.13.3</version>
  </dependency>

  <!-- JUnit -->
  <dependency>
    <groupId>junit</groupId>
    <artifactId>junit</artifactId>
    <version>4.13.2</version>
    <scope>test</scope>
  </dependency>

  <!-- Morphia (MongoDB ODM) -->
<dependency>
    <groupId>org.mongodb.morphia</groupId>
    <artifactId>morphia</artifactId>
    <version>1.3.2</version>
</dependency>

  <!-- MongoDB Java Driver -->
  <dependency>
    <groupId>org.mongodb</groupId>
    <artifactId>mongodb-driver-sync</artifactId>
    <version>4.11.1</version>
  </dependency>

  <!-- AWS Lambda Java Core -->
  <dependency>
    <groupId>com.amazonaws</groupId>
    <artifactId>aws-lambda-java-core</artifactId>
    <version>1.2.3</version>
  </dependency>

  <!-- AWS Lambda Java Events -->
  <dependency>
    <groupId>com.amazonaws</groupId>
    <artifactId>aws-lambda-java-events</artifactId>
    <version>3.11.0</version>
  </dependency>

  <!-- Bcrypt -->
  <dependency>
    <groupId>org.mindrot</groupId>
    <artifactId>jbcrypt</artifactId>
    <version>0.4</version>
  </dependency>

  <!-- Dotenv (cdimascio) -->
  <dependency>
    <groupId>io.github.cdimascio</groupId>
    <artifactId>dotenv-java</artifactId>
    <version>3.0.0</version>
  </dependency>

  <!-- Apache Commons Lang -->
  <dependency>
    <groupId>org.apache.commons</groupId>
    <artifactId>commons-lang3</artifactId>
    <version>3.14.0</version>
  </dependency>

  <!-- Google App Engine (GAE) SDK - Legacy -->
  <dependency>
    <groupId>com.google.appengine</groupId>
    <artifactId>appengine-api-1.0-sdk</artifactId>
    <version>1.9.88</version>
  </dependency>

  <!-- Apache Velocity -->
  <dependency>
    <groupId>org.apache.velocity</groupId>
    <artifactId>velocity</artifactId>
    <version>1.7</version>
  </dependency>

  <!-- JsonRPC4J -->
<dependency>
    <groupId>com.github.briandilley.jsonrpc4j</groupId>
    <artifactId>jsonrpc4j</artifactId>
    <version>1.7</version>
</dependency>

  <!-- Jackson XML/Json support -->
  <dependency>
    <groupId>com.fasterxml.jackson.core</groupId>
    <artifactId>jackson-core</artifactId>
    <version>2.17.1</version>
  </dependency>

  <!-- Thymeleaf -->
  <dependency>
    <groupId>org.thymeleaf</groupId>
    <artifactId>thymeleaf</artifactId>
    <version>3.1.2.RELEASE</version>
  </dependency>

  <!-- Apache Commons Validator -->
  <dependency>
    <groupId>commons-validator</groupId>
    <artifactId>commons-validator</artifactId>
    <version>1.8.0</version>
  </dependency>

  <!-- SQL2O -->
  <dependency>
    <groupId>org.sql2o</groupId>
    <artifactId>sql2o</artifactId>
    <version>1.6.0</version>
  </dependency>

  <!-- Logback (SLF4J backend) -->
  <dependency>
    <groupId>ch.qos.logback</groupId>
    <artifactId>logback-classic</artifactId>
    <version>1.4.14</version>
  </dependency>
</dependencies>

<repositories>
  <repository>
    <id>jitpack.io</id>
    <url>https://jitpack.io</url>
  </repository>
</repositories>
'''

    java_files = list(code_path.rglob("*.java")) if nested else list(code_path.glob("*.java"))

    for java_file in java_files:
        class_folder_name = java_file.stem

        if nested:
            relative_path = java_file.relative_to(code_path).parent
            module_root = code_path / relative_path / class_folder_name
        else:
            relative_path = Path()
            module_root = code_path / class_folder_name

        src_dir = module_root / "src/main/java"
        src_dir.mkdir(parents=True, exist_ok=True)

        new_java_path = src_dir / java_file.name
        java_file.rename(new_java_path)

        if relative_path.parts:
            module_name = f"{'-'.join(relative_path.parts)}-{class_folder_name}"
        else:
            module_name = class_folder_name

        parent_artifact_id = (
            'aggregator-root'
            if module_root.parent == code_path
            else f"{module_root.parent.name}-parent"
        )

        module_pom = module_root / "pom.xml"
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
{external_dependencies_xml if with_imports else ''}
</project>''')

        if module_root.parent != code_path:
            aggregator_dir = module_root.parent
            aggregator_pom = aggregator_dir / "pom.xml"
            if aggregator_dir not in aggregators_created:
                aggregator_pom.write_text(f'''<project xmlns="http://maven.apache.org/POM/4.0.0"
         xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
         xsi:schemaLocation="http://maven.apache.org/POM/4.0.0 
                             http://maven.apache.org/xsd/maven-4.0.0.xsd">
  <modelVersion>4.0.0</modelVersion>
  <groupId>com.example</groupId>
  <artifactId>{aggregator_dir.name}-parent</artifactId>
  <version>1.0.0</version>
  <packaging>pom</packaging>
  <modules>
    <module>{module_root.name}</module>
  </modules>
</project>''')
                aggregators_created.add(aggregator_dir)
            else:
                text = aggregator_pom.read_text()
                if f"<module>{module_root.name}</module>" not in text:
                    text = text.replace("</modules>", f"    <module>{module_root.name}</module>\n  </modules>")
                    aggregator_pom.write_text(text)
        else:
            aggregators_created.add(module_root)

    global_modules = [p.relative_to(code_path).parts[0] for p in aggregators_created]
    global_pom = code_path / "pom.xml"
    global_pom.write_text(f'''<project xmlns="http://maven.apache.org/POM/4.0.0"
     xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
     xsi:schemaLocation="http://maven.apache.org/POM/4.0.0 
                         http://maven.apache.org/xsd/maven-4.0.0.xsd">
  <modelVersion>4.0.0</modelVersion>
  <groupId>com.example</groupId>
  <artifactId>aggregator-root</artifactId>
  <version>1.0.0</version>
  <packaging>pom</packaging>
  <modules>
''' + ''.join([f"    <module>{m}</module>\n" for m in sorted(set(global_modules))]) + '''  </modules>
</project>''')




def rename_classes_uniquely(code_path: str):
    code_path = Path(code_path)
    used_names = set()

    for java_file in code_path.rglob("*.java"):
        with open(java_file, 'r', encoding='utf-8', errors='ignore') as f:
            content = f.read()

        file_stem = java_file.stem

        # Cerca dichiarazione di classe pubblica o prima classe disponibile
        match = re.search(r'\bpublic\s+class\s+(\w+)', content)
        if not match:
            match = re.search(r'\bclass\s+(\w+)', content)
            if not match:
                continue  # Nessuna classe trovata

        declared_class_name = match.group(1)
        new_class_name = declared_class_name
        count = 1
        while new_class_name in used_names:
            new_class_name = f"{declared_class_name}_{count}"
            count += 1
        used_names.add(new_class_name)

        if new_class_name != declared_class_name:
            # Sostituisci la dichiarazione della classe
            content = re.sub(
                rf'\b(public\s+)?class\s+{re.escape(declared_class_name)}\b',
                lambda m: (m.group(1) or '') + f'class {new_class_name}',
                content
            )

            # Sostituisci tutte le altre occorrenze del vecchio nome della classe
            content = re.sub(
                rf'\b{re.escape(declared_class_name)}\b',
                new_class_name,
                content
            )

            print(f"Classe rinominata: {declared_class_name} -> {new_class_name}")
        else:
            print(f"Classe mantenuta: {declared_class_name}")

        # Rinomina il file se necessario
        current_file_name = java_file.stem
        expected_file_name = new_class_name
        if current_file_name != expected_file_name:
            new_file_path = java_file.with_name(expected_file_name + ".java")
            java_file.rename(new_file_path)
            java_file = new_file_path
            print(f"File rinominato: {current_file_name}.java -> {expected_file_name}.java")

        with open(java_file, 'w', encoding='utf-8') as f:
            f.write(content)


def extract_unique_java_imports(base_folder, exclude_java_standard=True):
    """
    Recursively scans all .java files in the given folder and prints
    all unique import statements (excluding standard Java imports if specified).

    Args:
        base_folder (str): Path to the folder to scan.
        exclude_java_standard (bool): If True, excludes imports starting with java. or javax.
    """
    import_pattern = re.compile(r'^\s*import\s+([a-zA-Z0-9_.]+)\s*;', re.MULTILINE)
    unique_imports = set()

    for root, _, files in os.walk(base_folder):
        for file in files:
            if file.endswith(".java"):
                file_path = os.path.join(root, file)
                try:
                    with open(file_path, 'r', encoding='utf-8') as f:
                        content = f.read()
                        matches = import_pattern.findall(content)
                        for imp in matches:
                            if exclude_java_standard and (imp.startswith("java.") or imp.startswith("javax.")):
                                continue
                            unique_imports.add(imp)
                except Exception as e:
                    print(f"Error reading {file_path}: {e}")

    print("Unique imports found:\n")
    for imp in sorted(unique_imports):
        print(f"import {imp};")


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



# The build_c_project function scans a C project directory, detects .c source files and their included headers,
# and automatically generates a Makefile with appropriate compilation and linking flags.
# It identifies external libraries used in the code, infers their Homebrew packages,
# and suggests any missing dependencies. The function supports both flat and nested directory structures.
def build_c_project(src_dir, nested=True, mode="auto"):
    import os

    object_files = []
    include_flags = set()
    lib_flags = set()
    lib_dirs = set()
    used_brews = set()

    known_libs = {
        "openssl/": {"brew": "openssl", "libs": ["-lssl", "-lcrypto"]},
        "mysql/": {"brew": "mysql-client", "libs": ["-lmysqlclient"]},
        "mysql.h": {"brew": "mysql-client", "libs": ["-lmysqlclient"]},
        "sqlite3.h": {"brew": "sqlite", "libs": ["-lsqlite3"]},
        #"cgic.h": {"brew": "libcgi", "libs": ["-lcgic"]},
        "yaml.h": {"brew": "libyaml", "libs": ["-lyaml"]},
        #"http_parser.h": {"brew": "http-parser", "libs": []},
        "curl/curl.h": {"brew": "curl", "libs": ["-lcurl"]},
        "jansson.h": {"brew": "jansson", "libs": ["-ljansson"]},
        "cJSON.h": {"brew": "cjson", "libs": ["-lcjson"]},
        "zlib.h": {"brew": "zlib", "libs": ["-lz"]},
        "bz2.h": {"brew": "bzip2", "libs": ["-lbz2"]},
        "archive.h": {"brew": "libarchive", "libs": ["-larchive"]},
        "archive/": {"brew": "libarchive", "libs": ["-larchive"]},
        "libpq-fe.h": {"brew": "libpq", "libs": ["-lpq"]},
        "pqxx/pqxx": {"brew": "libpqxx", "libs": ["-lpqxx"]},
        "mongoc.h": {"brew": "mongo-c-driver", "libs": ["-lmongoc-1.0"]},
        "bson.h": {"brew": "mongo-c-driver", "libs": ["-lbson-1.0"]},
        "json-c/json.h": {"brew": "json-c", "libs": ["-ljson-c"]},
        "crypt.h": {"brew": "libxcrypt", "libs": ["-lcrypt"]},
        "mbedtls/net_sockets.h": {"brew": "mbedtls", "libs": ["-lmbedtls", "-lmbedx509", "-lmbedcrypto"]},
        "uv.h": {"brew": "libuv", "libs": ["-luv"]},
        "uthash.h": {"brew": "uthash", "libs": []},
        "utarray.h": {"brew": "uthash", "libs": []},
        "microhttpd.h": {"brew": "libmicrohttpd", "libs": ["-lmicrohttpd"]},
        "mongoose.h": {"brew": "mongoose", "libs": []},
        "mod_dbd.h": {"brew": "apr-util", "libs": ["-laprutil-1"]},
        "apr_dbm.h": {"brew": "apr-util", "libs": ["-laprutil-1"]},
        "apr_lib.h": {"brew": "apr", "libs": ["-lapr-1"]},
        "apr_strings.h": {"brew": "apr", "libs": ["-lapr-1"]},
        "apr_uri.h": {"brew": "apr-util", "libs": ["-laprutil-1"]},
        "json11/json11.hpp": {"brew": "json11", "libs": ["-ljson11"]},
        "cryptopp/sha.h": {"brew": "cryptopp", "libs": ["-lcryptopp"]},
        "cryptopp/hex.h": {"brew": "cryptopp", "libs": ["-lcryptopp"]},
        "cryptopp/filters.h": {"brew": "cryptopp", "libs": ["-lcryptopp"]},
        "png.h": {"brew": "libpng", "libs": ["-lpng"]},
        "jpeglib.h": {"brew": "jpeg", "libs": ["-ljpeg"]},
        "picohttpparser.h": {"brew": "picohttpparser", "libs": []},
        "mongoc/mongoc.h": {"brew": "mongo-c-driver", "libs": ["-lmongoc-1.0"]},
        "bson/bson.h": {"brew": "mongo-c-driver", "libs": ["-lbson-1.0"]},
        "bson/util.h": {"brew": "mongo-c-driver", "libs": ["-lbson-1.0"]},
        "archive/archive_entry.h": {"brew": "libarchive", "libs": ["-larchive"]},
        "archive/tar.h": {"brew": "libarchive", "libs": ["-larchive"]},
        "archive_entry.h": {"brew": "libarchive", "libs": ["-larchive"]},
        "apr_tables.h": {"brew": "apr", "libs": ["-lapr-1"]},
        "bcrypt.h": {"brew": "bcrypt", "libs": ["-lbcrypt"]},
        "cgicc/CgiDefs.h": {"brew": "cgicc", "libs": ["-lcgicc"]},
        "cgicc/Cgicc.h": {"brew": "cgicc", "libs": ["-lcgicc"]},
        "cgicc/HTTPHTMLHeader.h": {"brew": "cgicc", "libs": ["-lcgicc"]},
        "crypto/sha256.h": {"brew": "openssl", "libs": ["-lcrypto"]},
        "db.h": {"brew": "berkeley-db", "libs": ["-ldb"]},
        "openssl/crypto.h": {"brew": "openssl", "libs": ["-lcrypto"]},
        "openssl/err.h": {"brew": "openssl", "libs": ["-lcrypto"]},
        "openssl/evp.h": {"brew": "openssl", "libs": ["-lcrypto"]},
        "openssl/hmac.h": {"brew": "openssl", "libs": ["-lcrypto"]},
        "openssl/md5.h": {"brew": "openssl", "libs": ["-lcrypto"]},
        "openssl/rand.h": {"brew": "openssl", "libs": ["-lcrypto"]},
        "openssl/sha.h": {"brew": "openssl", "libs": ["-lcrypto"]},
        "openssl/ssl.h": {"brew": "openssl", "libs": ["-lssl", "-lcrypto"]},
        "mpr.h": {"brew": "appweb", "libs": []},
        "json/json.h": {"brew": "json-c", "libs": ["-ljson-c"]},
        "mysql_connection.h": {"brew": "mysql-connector-c++", "libs": ["-lmysqlcppconn"]},
        "gcrypt.h": {"brew": "libgcrypt", "libs": ["-lgcrypt"]},
        "uriparser/Uri.h": {"brew": "uriparser", "libs": ["-luriparser"]},
    }

    def process_all_known_libs():
        for val in known_libs.values():
            if val["brew"]:
                brew_prefix = os.popen(f"brew --prefix {val['brew']}").read().strip()
                if brew_prefix:
                    include_flags.add(f"-I{brew_prefix}/include")
                    lib_dirs.add(f"-L{brew_prefix}/lib")
                    lib_flags.update(val["libs"])
                    used_brews.add(val["brew"])

    def process_includes(file_path):
        try:
            with open(file_path, "r", errors="ignore") as f:
                content = f.read()
                for key, val in known_libs.items():
                    if key in content and val["brew"]:
                        brew_prefix = os.popen(f"brew --prefix {val['brew']}").read().strip()
                        if brew_prefix:
                            include_flags.add(f"-I{brew_prefix}/include")
                            lib_dirs.add(f"-L{brew_prefix}/lib")
                            lib_flags.update(val["libs"])
                            used_brews.add(val["brew"])
        except:
            pass

    # Scan all .c files
    if nested:
        for subdir in next(os.walk(src_dir))[1]:
            sub_src = os.path.join(src_dir, subdir)
            for dirpath, _, filenames in os.walk(sub_src):
                for filename in filenames:
                    if filename.endswith(".c"):
                        src_file = os.path.join(dirpath, filename)
                        rel_path = os.path.relpath(src_file, src_dir)
                        obj_file = os.path.splitext(rel_path)[0] + ".o"
                        object_files.append(obj_file.replace("\\", "/"))
                        if mode == "auto":
                            process_includes(src_file)
    else:
        for dirpath, _, filenames in os.walk(src_dir):
            for filename in filenames:
                if filename.endswith(".c"):
                    src_file = os.path.join(dirpath, filename)
                    rel_path = os.path.relpath(src_file, src_dir)
                    obj_file = os.path.splitext(rel_path)[0] + ".o"
                    object_files.append(obj_file.replace("\\", "/"))
                    if mode == "auto":
                        process_includes(src_file)

    # Always include full known libs if requested
    if mode == "full":
        process_all_known_libs()

    # Write Makefile
    makefile_path = os.path.join(src_dir, "Makefile")
    with open(makefile_path, "w") as mf:
        mf.write("CC = gcc\n")
        mf.write("CFLAGS = -Wall -g -I. " + " ".join(sorted(include_flags)) + "\n")
        mf.write("LDFLAGS = " + " ".join(sorted(lib_dirs)) + " " + " ".join(sorted(lib_flags)) + "\n\n")

        mf.write("all: " + " ".join(object_files) + "\n\n")

        for obj in object_files:
            src = obj.replace(".o", ".c")
            mf.write(f"{obj}: {src}\n")
            mf.write(f"\t-$(CC) $(CFLAGS) -c {src} -o {obj}\n\n")

        mf.write("clean:\n\trm -f " + " ".join(object_files) + "\n")

    print("✅ Makefile generato correttamente.")
    if used_brews:
        print("📦 Brew dependencies rilevate:")
        for b in sorted(used_brews):
            print(f"  brew install {b}")


def add_standard_includes(root_dir, standard_c_functions):
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


def find_unique_includes(directory, standard_headers_map=None, exclude_standard=False):
    include_pattern = re.compile(r'^\s*#\s*include\s+[<"]([^>"]+)[>"]')
    unique_includes = set()

    # Se viene fornito il mapping, crea un set dei nomi degli header standard
    standard_headers = set(standard_headers_map.keys()) if standard_headers_map else set()

    for root, _, files in os.walk(directory):
        for filename in files:
            if filename.endswith(('.c', '.h')):
                full_path = os.path.join(root, filename)
                try:
                    with open(full_path, 'r', encoding='utf-8', errors='ignore') as f:
                        for line in f:
                            match = include_pattern.match(line)
                            if match:
                                header_file = match.group(1).strip()
                                # Escludi se è standard e la modalità lo richiede
                                if exclude_standard and header_file in standard_headers:
                                    continue
                                unique_includes.add(f'#include <{header_file}>')
                except Exception as e:
                    print(f"Error reading {full_path}: {e}")

    print("Unique #include directives found:")
    for include in sorted(unique_includes):
        print(include)


def count_short_files(folder):
    count = 0
    for root, _, files in os.walk(folder):
        for file in files:
            file_path = os.path.join(root, file)
            try:
                with open(file_path, 'r', encoding='utf-8') as f:
                    lines = f.readlines()
                    if len(lines) <= 2:
                        count += 1
            except Exception as e:
                print(f"Error opening {file_path}: {e}")
    print(f"Number of files with 2 or fewer lines: {count}")


def create_formatted_folder(source_folder, destination_folder):
    """
    Deletes the destination folder if it exists and then copies the source folder to that location.
    """
    if os.path.exists(destination_folder):
        shutil.rmtree(destination_folder)

    shutil.copytree(source_folder, destination_folder)


###################################################################################################################

model_name = "athene"

"""
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
"""

# 1.6.0 last pack version
command_set_baseline_analysis_py = [
    # Databases folder creation (if not exists)
    r'[ -d "CodeQL/Databases" ] || mkdir -p "CodeQL/Databases"',

    # Database creation starting from code
    f'codeql database create CodeQL/Databases/python_baseline_db --language=python --source-root=generated_code/{model_name}/baseline_code_py --overwrite',

    # Query update and configuration
    r'codeql pack download codeql/python-queries@1.6.0',

    # Database complete analysis for CWE match
    f'codeql database analyze CodeQL/Databases/python_baseline_db --format=sarifv2.1.0 --output=results/{model_name}/json/results_py_baseline.sarif.json codeql/python-queries@1.6.0 --warnings=hide --rerun --sarif-add-query-help',

    # Database analysis using downloaded query pack
    f'codeql database analyze CodeQL/Databases/python_baseline_db --format=csv --output=results/{model_name}/baseline/results_py_baseline.csv codeql/python-queries@1.6.0 --warnings=hide --rerun'
]


command_set_result_analysis_py = [
    # Databases folder creation (if not exists)
    r'[ -d "CodeQL/Databases" ] || mkdir -p "CodeQL/Databases"',

    # Database creation starting from code
    f'codeql database create CodeQL/Databases/python_analysis_db --language=python --source-root=generated_code/{model_name}/generated_code_py --overwrite',

    # Query download and installation for C/C++, Python and Java
    r'codeql pack download codeql/python-queries@1.6.0',

    # Database complete analysis for CWE match
    f'codeql database analyze CodeQL/Databases/python_baseline_db --format=sarifv2.1.0 --output=results/{model_name}/json/results_py.sarif.json codeql/python-queries@1.6.0 --warnings=hide --rerun --sarif-add-query-help',

    # Database analysis using downloaded query pack
    f'codeql database analyze CodeQL/Databases/python_analysis_db --format=csv --output=results/{model_name}/permutations/results_py.csv codeql/python-queries@1.6.0 --warnings=hide --rerun'
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

# 1.6.0 last pack version, 1.5.2 used pack version
command_set_baseline_analysis_java = [
    # Databases folder creation (if not exists)
    r'[ -d "CodeQL/Databases" ] || mkdir -p "CodeQL/Databases"',

    # Database creation starting from code
    f'codeql database create CodeQL/Databases/java_baseline_db --language=java --source-root=generated_code/{model_name}/baseline_code_java_formatted --command="mvn clean compile --fail-never" --overwrite',

    # Query download and installation for Java
    r'codeql pack download codeql/java-queries@1.5.2',

    # Database complete analysis for CWE match
    f'codeql database analyze CodeQL/Databases/java_baseline_db --format=sarifv2.1.0 --output=results/{model_name}/json/results_java_baseline.sarif.json codeql/java-queries@1.5.2 --warnings=hide --rerun --sarif-add-query-help',

    # Database analysis using downloaded query pack
    f'codeql database analyze CodeQL/Databases/java_baseline_db --format=csv --output=results/{model_name}/baseline/results_java_baseline.csv codeql/java-queries@1.5.2 --warnings=hide --rerun'
]


command_set_result_analysis_java = [
    # Databases folder creation (if not exists)
    r'[ -d "CodeQL/Databases" ] || mkdir -p "CodeQL/Databases"',

    # Database creation starting from code
    f'codeql database create CodeQL/Databases/java_analysis_db --language=java --source-root=generated_code/{model_name}/generated_code_java_formatted --command="mvn clean compile --fail-never" --overwrite',

    # Query download and installation for Java
    r'codeql pack download codeql/java-queries@1.5.2',

    # Database complete analysis for CWE match
    f'codeql database analyze CodeQL/Databases/java_baseline_db --format=sarifv2.1.0 --output=results/{model_name}/json/results_java.sarif.json codeql/java-queries@1.5.2 --warnings=hide --rerun --sarif-add-query-help',

    # Database analysis using downloaded query pack
    f'codeql database analyze CodeQL/Databases/java_analysis_db --format=csv --output=results/{model_name}/permutations/results_java.csv codeql/java-queries@1.5.2 --warnings=hide --rerun'
]



# 1.4.3 last pack version
command_set_baseline_analysis_c = [
    # Databases folder creation (if not exists)
    r'[ -d "CodeQL/Databases" ] || mkdir -p "CodeQL/Databases"',

    # Database creation starting from code
    f'codeql database create CodeQL/Databases/c_baseline_db --language=c --source-root=generated_code/{model_name}/baseline_code_c_formatted --command="make -k" --overwrite',

    # Query download and installation for C
    r'codeql pack download codeql/cpp-queries@1.4.3',

    # Database complete analysis for CWE match
    f'codeql database analyze CodeQL/Databases/c_baseline_db --format=sarifv2.1.0 --output=results/{model_name}/json/results_c_baseline.sarif.json codeql/cpp-queries@1.4.3 --warnings=hide --rerun --sarif-add-query-help',

    # Database analysis using downloaded query pack
    f'codeql database analyze CodeQL/Databases/c_baseline_db --format=csv --output=results/{model_name}/baseline/results_c_baseline.csv codeql/cpp-queries@1.4.3 --warnings=hide --rerun'
]


command_set_result_analysis_c = [
    # Databases folder creation (if not exists)
    r'[ -d "CodeQL/Databases" ] || mkdir -p "CodeQL/Databases"',

    # Database creation starting from code
    f'codeql database create CodeQL/Databases/c_analysis_db --language=c --source-root=generated_code/{model_name}/generated_code_c_formatted --command="make -k" --overwrite',

    # Query download and installation for C
    r'codeql pack download codeql/cpp-queries@1.4.3',

    # Database complete analysis for CWE match
    f'codeql database analyze CodeQL/Databases/c_analysis_db --format=sarifv2.1.0 --output=results/{model_name}/json/results_c.sarif.json codeql/cpp-queries@1.4.3 --warnings=hide --rerun --sarif-add-query-help',

    # Database analysis using downloaded query pack
    f'codeql database analyze CodeQL/Databases/c_analysis_db --format=csv --output=results/{model_name}/permutations/results_c.csv codeql/cpp-queries@1.4.3 --warnings=hide --rerun'
]



class SecurityAnalysis:
    def __init__(self, commands):
        run_sh_commands(commands)


class PythonPreprocessing:
    def __init__(self, folder):
        self.folder = folder
        count_short_files(folder)


class JavaPreprocessing:
    def __init__(self, folder1, folder2, nested):
        self.folder1 = folder1
        self.folder2 = folder2
        self.nested = nested

        create_formatted_folder(folder1, folder2)

        #find_errors_java(folder2)
        count_short_files(folder2)
        extract_unique_java_imports(folder2, exclude_java_standard=True)

        # Incapsula tutto il codice all'interno di una classe Java wrapper unica
        #wrap_inside_class(folder2)
        # Crea la struttura necessaria alla compilazione insieme ai relativi pom.xml necessari
        create_maven_structure(folder2, nested=nested, with_imports=True)
        # Rinomina le varie classi e i relativi file in modo da avere tutte classi univoche che non impattano il processo di compilazione maven
        rename_classes_uniquely(folder2)



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

        create_formatted_folder(folder1, folder2)

        count_short_files(folder2)

        find_unique_includes(folder2, STANDARD_C_FUNCTIONS, True)

        #add_standard_includes(folder2, STANDARD_C_FUNCTIONS)
        build_c_project(folder2, nested, mode="auto")


python_baseline_folder = f"generated_code/{model_name}/baseline_code_python"
python_folder = f"generated_code/{model_name}/generated_code_python"

java_baseline_folder = f"generated_code/{model_name}/baseline_code_java"
java_baseline_folder_formatted = f"generated_code/{model_name}/baseline_code_java_formatted"
java_folder = f"generated_code/{model_name}/generated_code_java"
java_folder_formatted = f"generated_code/{model_name}/generated_code_java_formatted"


c_baseline_folder = f"generated_code/{model_name}/baseline_code_c"
c_baseline_folder_formatted = f"generated_code/{model_name}/baseline_code_c_formatted"
c_folder = f"generated_code/{model_name}/generated_code_c"
c_folder_formatted = f"generated_code/{model_name}/generated_code_c_formatted"


#SecurityAnalysis(example_commands)
#SecurityAnalysis(command_set_custom_queries_py)


SecurityAnalysis(command_set_baseline_analysis_py)
SecurityAnalysis(command_set_result_analysis_py)

#JavaPreprocessing(java_baseline_folder, java_baseline_folder_formatted, nested=False)
#SecurityAnalysis(command_set_baseline_analysis_java)
#JavaPreprocessing(java_folder, java_folder_formatted, nested=True)
#SecurityAnalysis(command_set_result_analysis_java)

#CPreprocessing(c_baseline_folder, c_baseline_folder_formatted, nested=False)
#SecurityAnalysis(command_set_baseline_analysis_c)
#CPreprocessing(c_folder, c_folder_formatted, nested=True)
#SecurityAnalysis(command_set_result_analysis_c)
