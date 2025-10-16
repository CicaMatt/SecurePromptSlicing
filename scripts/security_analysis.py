import ast
import json
import math
import os
import re
import shutil
import subprocess
import warnings
from pathlib import Path

warnings.filterwarnings("ignore", category=SyntaxWarning)



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


def create_maven_structure(code_path: str, nested: bool = False, with_imports: bool = False):
    code_path = Path(code_path)
    aggregators_created = set()

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
    <groupId>com.mysql</groupId>
    <artifactId>mysql-connector-j</artifactId>
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
  
  <dependency>
    <groupId>com.sparkjava</groupId>
    <artifactId>spark-template-thymeleaf</artifactId>
    <version>2.7.1</version>
    </dependency>
    
  <!-- org.json -->
  <dependency>
    <groupId>org.json</groupId>
    <artifactId>json</artifactId>
    <version>20240303</version>
  </dependency>
    
    <!-- StringTemplate v4 -->
  <dependency>
    <groupId>org.antlr</groupId>
    <artifactId>ST4</artifactId>
    <version>4.3.4</version>
  </dependency>

    <!-- Spark template engines used in your imports -->
  <dependency>
    <groupId>com.sparkjava</groupId>
    <artifactId>spark-template-handlebars</artifactId>
    <version>2.7.1</version>
  </dependency>
  <dependency>
    <groupId>com.sparkjava</groupId>
    <artifactId>spark-template-mustache</artifactId>
    <version>2.7.1</version>
  </dependency>
  <dependency>
    <groupId>com.sparkjava</groupId>
    <artifactId>spark-template-velocity</artifactId>
    <version>2.7.1</version>
  </dependency>
    
    <!-- Spring Session (required for the org.springframework.session.* imports/annotations) -->
  <dependency>
    <groupId>org.springframework.session</groupId>
    <artifactId>spring-session-core</artifactId>
    <version>3.2.3</version>
  </dependency>
  <dependency>
    <groupId>org.springframework.session</groupId>
    <artifactId>spring-session-data-redis</artifactId>
    <version>3.2.3</version>
  </dependency>
  <dependency>
    <groupId>org.springframework.session</groupId>
    <artifactId>spring-session-jdbc</artifactId>
    <version>3.2.3</version>
  </dependency>
  
  <dependency>
    <groupId>jakarta.ws.rs</groupId>
    <artifactId>jakarta.ws.rs-api</artifactId>
    <version>3.1.0</version>
  </dependency>
  
  <dependency>
    <groupId>org.glassfish.jersey.core</groupId>
    <artifactId>jersey-server</artifactId>
    <version>3.1.6</version>
  </dependency>

<!-- Jython (for org.python.* classes) -->
  <dependency>
    <groupId>org.python</groupId>
    <artifactId>jython-standalone</artifactId>
    <version>2.7.4</version>
  </dependency>
  
  <dependency>
    <groupId>com.github.spullara.mustache.java</groupId>
    <artifactId>compiler</artifactId>
    <version>0.9.10</version>
  </dependency>

<!-- HikariCP (com.zaxxer.hikari.*) -->
  <dependency>
    <groupId>com.zaxxer</groupId>
    <artifactId>HikariCP</artifactId>
    <version>5.1.0</version>
  </dependency>

<!-- FreeMarker core (freemarker.template.*) -->
  <dependency>
    <groupId>org.freemarker</groupId>
    <artifactId>freemarker</artifactId>
    <version>2.3.32</version>
  </dependency>

<!-- ClassGraph (io.github.classgraph.*) -->
  <dependency>
    <groupId>io.github.classgraph</groupId>
    <artifactId>classgraph</artifactId>
    <version>4.8.172</version>
  </dependency>

<!-- JJWT (io.jsonwebtoken.*) -->
  <dependency>
    <groupId>io.jsonwebtoken</groupId>
    <artifactId>jjwt-api</artifactId>
    <version>0.12.6</version>
  </dependency>
  <dependency>
    <groupId>io.jsonwebtoken</groupId>
    <artifactId>jjwt-impl</artifactId>
    <version>0.12.6</version>
    <scope>runtime</scope>
  </dependency>
  <dependency>
    <groupId>io.jsonwebtoken</groupId>
    <artifactId>jjwt-jackson</artifactId>
    <version>0.12.6</version>
    <scope>runtime</scope>
  </dependency>

<!-- Vert.x (io.vertx.*) -->
  <dependency>
    <groupId>io.vertx</groupId>
    <artifactId>vertx-core</artifactId>
    <version>4.5.8</version>
  </dependency>
  <dependency>
    <groupId>io.vertx</groupId>
    <artifactId>vertx-web</artifactId>
    <version>4.5.8</version>
  </dependency>
  <dependency>
    <groupId>io.vertx</groupId>
    <artifactId>vertx-pg-client</artifactId>
    <version>4.5.8</version>
  </dependency>

<!-- Commons DbUtils (org.apache.commons.dbutils.*) -->
  <dependency>
    <groupId>commons-dbutils</groupId>
    <artifactId>commons-dbutils</artifactId>
    <version>1.8.1</version>
  </dependency>

<!-- PDFBox (org.apache.pdfbox.*) -->
  <dependency>
    <groupId>org.apache.pdfbox</groupId>
    <artifactId>pdfbox</artifactId>
    <version>2.0.31</version>
  </dependency>

<!-- H2 (org.h2.jdbcx.*) -->
  <dependency>
    <groupId>com.h2database</groupId>
    <artifactId>h2</artifactId>
    <version>2.2.224</version>
    <scope>test</scope>
  </dependency>

<!-- JetBrains annotations (org.jetbrains.annotations.*) -->
  <dependency>
    <groupId>org.jetbrains</groupId>
    <artifactId>annotations</artifactId>
    <version>24.1.0</version>
  </dependency>

<!-- Jersey extras used by your imports -->
  <dependency>
    <groupId>org.glassfish.jersey.containers</groupId>
    <artifactId>jersey-container-grizzly2-http</artifactId>
    <version>3.1.6</version>
  </dependency>
  <dependency>
    <groupId>org.glassfish.jersey.containers</groupId>
    <artifactId>jersey-container-jetty-http</artifactId>
    <version>3.1.6</version>
  </dependency>
  <dependency>
    <groupId>org.glassfish.jersey.media</groupId>
    <artifactId>jersey-media-json-jackson</artifactId>
    <version>3.1.6</version>
  </dependency>
  <dependency>
    <groupId>org.glassfish.jersey.ext</groupId>
    <artifactId>jersey-mvc-jsp</artifactId>
    <version>3.1.6</version>
  </dependency>

<!-- Spring Security crypto (BCryptPasswordEncoder) -->
  <dependency>
    <groupId>org.springframework.security</groupId>
    <artifactId>spring-security-crypto</artifactId>
    <version>6.2.4</version>
  </dependency>
  <dependency>
    <groupId>org.apache.tomcat</groupId>
    <artifactId>tomcat-jdbc</artifactId>
    <version>10.1.24</version> <!-- usa la versione compatibile con la tua distribuzione -->
  </dependency>
  <dependency>
    <groupId>javax.xml.bind</groupId>
    <artifactId>jaxb-api</artifactId>
    <version>2.3.1</version>
  </dependency>
  <dependency>
    <groupId>org.glassfish.jaxb</groupId>
    <artifactId>jaxb-runtime</artifactId>
    <version>2.3.8</version>
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

        match = re.search(r'\bpublic\s+class\s+(\w+)', content)
        if not match:
            match = re.search(r'\bclass\s+(\w+)', content)
            if not match:
                continue

        declared_class_name = match.group(1)
        new_class_name = declared_class_name
        count = 1
        while new_class_name in used_names:
            new_class_name = f"{declared_class_name}_{count}"
            count += 1
        used_names.add(new_class_name)

        if new_class_name != declared_class_name:
            content = re.sub(
                rf'\b(public\s+)?class\s+{re.escape(declared_class_name)}\b',
                lambda m: (m.group(1) or '') + f'class {new_class_name}',
                content
            )

            content = re.sub(
                rf'\b{re.escape(declared_class_name)}\b',
                new_class_name,
                content
            )

            print(f"Classe rinominata: {declared_class_name} -> {new_class_name}")
        else:
            print(f"Classe mantenuta: {declared_class_name}")

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
        "yaml.h": {"brew": "libyaml", "libs": ["-lyaml"]},
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
        "json/json.h": {"brew": "jsoncpp", "libs": ["-ljsoncpp"]},
        "httpserver.hpp": {"brew": "libhttpserver", "libs": ["-lhttpserver"]},
        "mysql_connection.h": {"brew": "mysql-connector-c++", "libs": ["-lmysqlcppconn"]},
        "gcrypt.h": {"brew": "libgcrypt", "libs": ["-lgcrypt"]},
        "uriparser/Uri.h": {"brew": "uriparser", "libs": ["-luriparser"]},
        "libyaml.h": {"brew": "libyaml", "libs": ["-lyaml"]},
        "tar.h": {"brew": "libtar", "libs": ["-ltar"]},
        "pcre.h": {"brew": "pcre", "libs": ["-lpcre"]},
        "zip.h": {"brew": "libzip", "libs": ["-lzip"]},
        "openssl/bio.h": {"brew": "openssl", "libs": ["-lcrypto"]},
        "libyaml/parser.h": {"brew": "libyaml", "libs": ["-lyaml"]},
        "libyaml/yaml.h": {"brew": "libyaml", "libs": ["-lyaml"]},
        "arpa/inet.h": {"brew": None, "libs": []},
        "esp_http_server.h": {"brew": None, "libs": ["-lesp_http_server"]},
        "esp_system.h": {"brew": None, "libs": ["-lesp_system"]},
        "nvs_flash.h": {"brew": None, "libs": ["-lnvs_flash"]},
        "fcntl.h": {"brew": None, "libs": []},
        "sys/socket.h": {"brew": None, "libs": []},
        "sys/stat.h": {"brew": None, "libs": []},
        "sys/types.h": {"brew": None, "libs": []},
        "unistd.h": {"brew": None, "libs": []},
        "regex.h": {"brew": "pcre", "libs": ["-lpcre"]},
        "openssl/buffer.h": {"brew": "openssl", "libs": ["-lcrypto"]},
        "bzlib.h": {"brew": "bzip2", "libs": ["-lbz2"]},
        "cgi.h": {"brew": "libcgi", "libs": ["-lcgi"]},
        "http_parser.h": {"brew": "http-parser", "libs": ["-lhttp_parser"]},
        "mysql/mysql.h": {"brew": "mysql-client", "libs": ["-lmysqlclient"]},
        "msgpack.h": {"brew": "msgpack", "libs": ["-lmsgpackc"]},
        "sql.h": {"brew": "unixodbc", "libs": ["-lodbc"]},
        "sqlext.h": {"brew": "unixodbc", "libs": ["-lodbc"]},
        "openssl/pem.h": {"brew": "openssl", "libs": ["-lssl", "-lcrypto"]},
        "uvc.h": {"brew": "libuvc", "libs": ["-luvc"]},
        "libuvc/libuvc.h": {"brew": "libuvc", "libs": ["-luvc"]},
        "httpd.h": {"brew": "httpd", "libs": []},
        "http_config.h": {"brew": "httpd", "libs": []},
        "http_protocol.h": {"brew": "httpd", "libs": []},
        "http_request.h": {"brew": "httpd", "libs": []},
        "http_server.h": {"brew": "httpd", "libs": []},
        "libarchive/archive.h": {"brew": "libarchive", "libs": ["-larchive"]},
        "libarchive/archive_entry.h": {"brew": "libarchive", "libs": ["-larchive"]},
        "dirent.h": {"brew": None, "libs": []},
        "direct.h": {"brew": None, "libs": []},
        "netinet/in.h": {"brew": None, "libs": []},
        "windows.h": {"brew": None, "libs": []},
        "libmicrohttpd.h": {"brew": "libmicrohttpd", "libs": ["-lmicrohttpd"]},
        "libbase64.h": {"brew": None, "libs": ["-lbase64"]},
    "Windows.h": {"brew": None, "libs": []},
    "ap_config.h": {"brew": "httpd", "libs": []},
    "http_log.h": {"brew": "httpd", "libs": []},
    "event2/event.h": {"brew": "libevent", "libs": ["-levent"]},
    "event2/http.h": {"brew": "libevent", "libs": ["-levent"]},
    "event2/buffer.h": {"brew": "libevent", "libs": ["-levent"]},
    "event2/listener.h": {"brew": "libevent", "libs": ["-levent"]},
    "event2/util.h": {"brew": "libevent", "libs": ["-levent"]},
    "libwebsockets.h": {"brew": "libwebsockets", "libs": ["-lwebsockets"]},
    "mod_wsgi/include/mod_wsgi-api.h": {"brew": "mod_wsgi", "libs": []},
    "yaml-cpp/yaml.h": {"brew": "yaml-cpp", "libs": ["-lyaml-cpp"]},
    "emscripten.h": {"brew": "emscripten", "libs": []},
    "emscripten/html5.h": {"brew": "emscripten", "libs": []},
    "lodepng.h": {"brew": None, "libs": []},
    "miniz.h": {"brew": None, "libs": []},
    "base64.h": {"brew": None, "libs": ["-lbase64"]},
    "pthread.h": {"brew": None, "libs": ["-lpthread"]},
    "httpserver.h": {"brew": "libhttpserver", "libs": ["-lhttpserver"]},
    "io.h": {"brew": None, "libs": []},
    "libgen.h": {"brew": None, "libs": []},
    "netdb.h": {"brew": None, "libs": []},
    "winsock2.h": {"brew": None, "libs": []},
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

    if mode == "full":
        process_all_known_libs()

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


def find_unique_includes(directory, standard_headers_map=None, exclude_standard=False):
    include_pattern = re.compile(r'^\s*#\s*include\s+[<"]([^>"]+)[>"]')
    unique_includes = set()

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
    for root, dirs, files in os.walk(folder):
        if "__pycache__" in dirs:
            dirs.remove("__pycache__")

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


def collect_python_imports(root_dir: str):
    imports = set()

    for dirpath, dirnames, filenames in os.walk(root_dir):
        dirnames[:] = [d for d in dirnames if d != "__pycache__"]

        for filename in filenames:
            if not filename.endswith(".py"):
                continue

            filepath = os.path.join(dirpath, filename)
            try:
                with open(filepath, "r", encoding="utf-8", errors="ignore") as f:
                    node = ast.parse(f.read(), filename=filepath)

                for n in ast.walk(node):
                    if isinstance(n, ast.Import):
                        for alias in n.names:
                            imports.add(alias.name.split(".")[0])
                    elif isinstance(n, ast.ImportFrom):
                        if n.module is not None:
                            imports.add(n.module.split(".")[0])
            except Exception:
                continue

    for mod in sorted(imports):
        print(mod)

    return imports


def create_formatted_folder(source_folder, destination_folder):
    if os.path.exists(destination_folder):
        shutil.rmtree(destination_folder)

    shutil.copytree(source_folder, destination_folder)


def parse_codeql_sarif_c(sarif_path, print_report=True, show_lists=False):
    sarif_path = Path(sarif_path)
    data = json.loads(sarif_path.read_text(encoding="utf-8"))

    artifacts_seen = 0
    analyzed_uris = set()
    expected_uris = set()
    files_with_snippets_uris = set()
    extraction_warning_uris = set()

    extractor_successes = 0
    extractor_failures = 0
    _saw_extractor_summary = False

    runs = data.get("runs", []) or []
    for run in runs:
        artifacts = run.get("artifacts", []) or []
        artifacts_seen += len(artifacts)

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

        def _collect_uris_from_locations(obj):
            out = []
            for loc in (obj.get("locations", []) or []):
                phys = (loc.get("physicalLocation") or {})
                art = (phys.get("artifactLocation") or {})
                uri = _uri_from_artloc(art)
                if uri:
                    out.append(uri)
            for rloc in (obj.get("relatedLocations", []) or []):
                phys = (rloc.get("physicalLocation") or {})
                art = (rloc.get("artifactLocation") or {})
                uri = _uri_from_artloc(art)
                if uri:
                    out.append(uri)
            return out

        diag_rule_ids = {
            "cpp/baseline/expected-extracted-files",
            "cpp/diagnostics/successfully-extracted-files",
            "cpp/diagnostics/extraction-warnings",
            "cpp/diagnostics/failed-extractor-invocations",
        }

        for res in run.get("results", []) or []:
            rid = res.get("ruleId") or (res.get("rule") or {}).get("id")
            if rid in diag_rule_ids:
                continue
            for uri in _collect_uris_from_locations(res):
                analyzed_uris.add(uri)

        for inv in run.get("invocations", []) or []:
            for tn in inv.get("toolExecutionNotifications", []) or []:
                desc = (tn.get("descriptor") or {})
                desc_id = desc.get("id") or tn.get("id") or tn.get("name") or ""

                if desc_id == "cpp/baseline/expected-extracted-files":
                    for uri in _collect_uris_from_locations(tn):
                        expected_uris.add(uri)

                elif desc_id == "cpp/extractor/summary":
                    if not _saw_extractor_summary:
                        attrs = ((tn.get("properties") or {}).get("attributes")) or {}
                        extractor_successes += int(attrs.get("extractor-successes") or 0)
                        extractor_failures  += int(attrs.get("extractor-failures") or 0)
                        _saw_extractor_summary = True

                elif desc_id == "cpp/diagnostics/successfully-extracted-files":
                    for uri in _collect_uris_from_locations(tn):
                        files_with_snippets_uris.add(uri)

                elif desc_id == "cpp/diagnostics/extraction-warnings":
                    for uri in _collect_uris_from_locations(tn):
                        extraction_warning_uris.add(uri)

        diag_to_set = {
            "cpp/baseline/expected-extracted-files": expected_uris,
            "cpp/diagnostics/successfully-extracted-files": files_with_snippets_uris,
            "cpp/diagnostics/extraction-warnings": extraction_warning_uris,
        }
        for res in run.get("results", []) or []:
            rid = res.get("ruleId") or (res.get("rule") or {}).get("id")
            dest_set = diag_to_set.get(rid)
            if dest_set is not None:
                for uri in _collect_uris_from_locations(res):
                    dest_set.add(uri)

        for notif in (run.get("tool", {}).get("driver", {}).get("notifications", []) or []):
            nid = notif.get("id") or notif.get("name") or ""
            if nid == "cpp/extractor/summary":
                if not _saw_extractor_summary:
                    attrs = ((notif.get("properties") or {}).get("attributes")) or {}
                    extractor_successes += int(attrs.get("extractor-successes") or 0)
                    extractor_failures  += int(attrs.get("extractor-failures") or 0)
                    _saw_extractor_summary = True
            elif nid == "cpp/diagnostics/successfully-extracted-files":
                for uri in _collect_uris_from_locations(notif):
                    files_with_snippets_uris.add(uri)
            elif nid == "cpp/diagnostics/extraction-warnings":
                for uri in _collect_uris_from_locations(notif):
                    extraction_warning_uris.add(uri)
            elif nid == "cpp/baseline/expected-extracted-files":
                for uri in _collect_uris_from_locations(notif):
                    expected_uris.add(uri)

    files_expected = len(expected_uris)
    files_with_snippets = len(files_with_snippets_uris)
    files_without_snippets = max(0, files_expected - files_with_snippets)

    warnings_with_snippets = len(extraction_warning_uris & files_with_snippets_uris)
    warnings_without_snippets = len(extraction_warning_uris - files_with_snippets_uris)

    extractor_total = extractor_successes + extractor_failures

    summary = {
        "extractor_successes": extractor_successes,
        "extractor_failures": extractor_failures,
        "extractor_total": extractor_total,
        "files_expected": files_expected,
        "files_with_snippets": files_with_snippets,
        "files_without_snippets": files_without_snippets,
        "warnings_with_snippets": warnings_with_snippets,
        "warnings_without_snippets": warnings_without_snippets,
        "analyzed_files": len(analyzed_uris),
        "artifacts_seen": artifacts_seen,
        "expected_uris": sorted(expected_uris) if show_lists else [],
        "analyzed_uris": sorted(analyzed_uris) if show_lists else [],
        "successfully_extracted_uris": sorted(files_with_snippets_uris) if show_lists else [],
        "extraction_warning_uris": sorted(extraction_warning_uris) if show_lists else [],
    }

    if print_report:
        print("== CodeQL SARIF – C/C++ – Riepilogo ==")

        print("Invocazioni estrattore:")
        print(f"  OK (senza interruzioni):        {summary['extractor_successes']}")
        print(f"  KO (non giunte a termine):      {summary['extractor_failures']}")
        print(f"  Totale:                         {summary['extractor_total']}")

        print()
        print("File:")
        print(f"  Attesi (baseline):              {summary['files_expected']}")
        print(f"  Estratti:                       {summary['files_with_snippets']}")
        print(f"    ├─ di cui con warning:        {summary['warnings_with_snippets']}")
        print(f"    └─ di cui senza warning:      {summary['files_with_snippets'] - summary['warnings_with_snippets']}")
        print(f"  Non estratti:                   {summary['files_without_snippets']}")
        print()
        print(f"File citati nei risultati (query): {summary['analyzed_files']}")

        if show_lists:
            print("\n-- Lista attesi per estrazione (baseline) --")
            for u in summary["expected_uris"]:
                print(" ", u)
            print("\n-- Lista file con match sulle query (non diagnostica) --")
            for u in summary["analyzed_uris"]:
                print(" ", u)
            print("\n-- Lista file con snippet (successfully-extracted-files) --")
            for u in summary["successfully_extracted_uris"]:
                print(" ", u)
            print("\n-- Lista file con warning di estrazione --")
            for u in summary["extraction_warning_uris"]:
                print(" ", u)

    return summary


def parse_codeql_sarif_c_merged(sarif_a, sarif_b, sarif_c, print_report=True, rounding="nearest"):
    if "parse_codeql_sarif_c" not in globals():
        raise RuntimeError("Devi definire 'parse_codeql_sarif_c' nello scope prima di usare questa funzione.")

    def _iround(x: float) -> int:
        if rounding == "nearest":
            return int(round(x))
        if rounding == "floor":
            return math.floor(x)
        if rounding == "ceil":
            return math.ceil(x)
        raise ValueError("rounding deve essere 'nearest', 'floor' o 'ceil'.")

    numeric_keys = [
        "extractor_successes",
        "extractor_failures",
        "extractor_total",
        "files_expected",
        "files_with_snippets",
        "files_without_snippets",
        "warnings_with_snippets",
        "warnings_without_snippets",
        "analyzed_files",
    ]

    sums = {k: 0 for k in numeric_keys}

    for path in (sarif_a, sarif_b, sarif_c):
        summary = parse_codeql_sarif_c(path, print_report=False, show_lists=False)
        for k in numeric_keys:
            sums[k] += int(summary.get(k, 0))

    avgs = {k: _iround(sums[k] / 3.0) for k in numeric_keys}

    if print_report:
        print("== CodeQL SARIF – C/C++ – Medie su 3 file ==")
        print("Invocazioni estrattore (medie):")
        print(f"  OK (senza interruzioni):        {avgs['extractor_successes']}")
        print(f"  KO (non giunte a termine):      {avgs['extractor_failures']}")
        print(f"  Totale:                         {avgs['extractor_total']}")
        print()
        print("File (medie):")
        print(f"  Attesi (baseline):              {avgs['files_expected']}")
        print(f"  Estratti:                       {avgs['files_with_snippets']}")
        estratti_senza_warning = avgs['files_with_snippets'] - avgs['warnings_with_snippets']
        print(f"    ├─ di cui con warning:        {avgs['warnings_with_snippets']}")
        print(f"    └─ di cui senza warning:      {estratti_senza_warning}")
        print(f"  Non estratti:                   {avgs['files_without_snippets']}")
        print()
        print(f"File citati nei risultati (query): {avgs['analyzed_files']}")

    return avgs


def parse_codeql_sarif_java(sarif_path, print_report=True, show_lists=False):
    sarif_path = Path(sarif_path)
    data = json.loads(sarif_path.read_text(encoding="utf-8"))

    artifacts_seen = 0
    expected_uris = set()
    success_uris = set()
    warning_uris = set()
    error_uris = set()
    analyzed_uris = set()

    runs = data.get("runs", []) or []
    for run in runs:
        artifacts = run.get("artifacts", []) or []
        artifacts_seen += len(artifacts)

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

        def _collect_uris(obj):
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

        diag_rule_ids = {
            "java/baseline/expected-extracted-files",
            "java/diagnostics/successfully-extracted-files",
            "java/diagnostics/extraction-warnings",
            "java/diagnostics/extraction-errors",
            "java/diagnostic/database-quality",
        }
        for res in run.get("results", []) or []:
            rid = res.get("ruleId") or (res.get("rule") or {}).get("id")
            if rid in diag_rule_ids:
                continue
            for uri in _collect_uris(res):
                analyzed_uris.add(uri)

        for inv in run.get("invocations", []) or []:
            for tn in inv.get("toolExecutionNotifications", []) or []:
                desc_id = (tn.get("descriptor") or {}).get("id") or tn.get("id") or tn.get("name") or ""
                dest = None
                if desc_id == "java/baseline/expected-extracted-files":
                    dest = expected_uris
                elif desc_id == "java/diagnostics/successfully-extracted-files":
                    dest = success_uris
                elif desc_id == "java/diagnostics/extraction-warnings":
                    dest = warning_uris
                elif desc_id == "java/diagnostics/extraction-errors":
                    dest = error_uris
                if dest is not None:
                    for uri in _collect_uris(tn):
                        dest.add(uri)

        diag_map = {
            "java/baseline/expected-extracted-files": expected_uris,
            "java/diagnostics/successfully-extracted-files": success_uris,
            "java/diagnostics/extraction-warnings": warning_uris,
            "java/diagnostics/extraction-errors": error_uris,
        }
        for res in run.get("results", []) or []:
            rid = res.get("ruleId") or (res.get("rule") or {}).get("id")
            dest = diag_map.get(rid)
            if dest is not None:
                for uri in _collect_uris(res):
                    dest.add(uri)

        for notif in (run.get("tool", {}).get("driver", {}).get("notifications", []) or []):
            nid = notif.get("id") or notif.get("name") or ""
            dest = None
            if nid == "java/baseline/expected-extracted-files":
                dest = expected_uris
            elif nid == "java/diagnostics/successfully-extracted-files":
                dest = success_uris
            elif nid == "java/diagnostics/extraction-warnings":
                dest = warning_uris
            elif nid == "java/diagnostics/extraction-errors":
                dest = error_uris
            if dest is not None:
                for uri in _collect_uris(notif):
                    dest.add(uri)

    files_expected = len(expected_uris)
    files_extracted = len(success_uris)
    files_not_extracted = max(0, files_expected - files_extracted)

    summary = {
        "artifacts_seen": artifacts_seen,
        "files_expected": files_expected,
        "files_extracted": files_extracted,
        "files_not_extracted": files_not_extracted,
        "extraction_warnings": len(warning_uris),
        "extraction_errors": len(error_uris),
        "analyzed_files": len(analyzed_uris),

        "expected_uris": sorted(expected_uris),
        "success_uris": sorted(success_uris),
        "analyzed_uris": sorted(analyzed_uris),
        "warning_uris": sorted(warning_uris),
        "error_uris": sorted(error_uris),
    }

    if print_report:
        print("== CodeQL SARIF – Java – Riepilogo ==")
        print(f"Artefatti registrati nel SARIF:       {summary['artifacts_seen']}")
        print(f"File attesi (baseline):               {summary['files_expected']}")
        print(f"File estratti (nel DB):               {summary['files_extracted']}")
        print(f"File non estratti (non nel DB):       {summary['files_not_extracted']}")
        print(f"Warning di estrazione (.java):        {summary['extraction_warnings']}")
        print(f"Errori di estrazione (.java):         {summary['extraction_errors']}")
        print(f"File citati nei risultati (query):    {summary['analyzed_files']}")

        if show_lists:
            def _dump(title, items):
                print(f"\n-- {title} ({len(items)}) --")
                for u in items:
                    print(" ", u)

            _dump("Expected (baseline)", summary["expected_uris"])
            _dump("Successfully extracted", summary["success_uris"])
            _dump("Files con risultati (non diagnostica)", summary["analyzed_uris"])

    return summary


def parse_codeql_sarif_java_merged(sarif_a, sarif_b, sarif_c, print_report=True, rounding="nearest"):
    if "parse_codeql_sarif_java" not in globals():
        raise RuntimeError("Devi definire 'parse_codeql_sarif_java' nello scope prima di usare questa funzione.")

    def _iround(x: float) -> int:
        if rounding == "nearest":
            return int(round(x))
        if rounding == "floor":
            return math.floor(x)
        if rounding == "ceil":
            return math.ceil(x)
        raise ValueError("rounding deve essere 'nearest', 'floor' o 'ceil'.")

    numeric_keys = [
        "artifacts_seen",
        "files_expected",
        "files_extracted",
        "files_not_extracted",
        "extraction_warnings",
        "extraction_errors",
        "analyzed_files",
    ]

    sums = {k: 0 for k in numeric_keys}
    for path in (sarif_a, sarif_b, sarif_c):
        summary = parse_codeql_sarif_java(path, print_report=False, show_lists=False)
        for k in numeric_keys:
            sums[k] += int(summary.get(k, 0))

    avgs = {k: _iround(sums[k] / 3.0) for k in numeric_keys}

    if print_report:
        print("== CodeQL SARIF – Java – Medie su 3 file ==")
        print(f"Artefatti registrati (media):         {avgs['artifacts_seen']}")
        print(f"File attesi (baseline, media):        {avgs['files_expected']}")
        print(f"File estratti (DB, media):            {avgs['files_extracted']}")
        print(f"File non estratti (media):            {avgs['files_not_extracted']}")
        print(f"Warning di estrazione (media):        {avgs['extraction_warnings']}")
        print(f"Errori di estrazione (media):         {avgs['extraction_errors']}")
        print(f"File citati nei risultati (media):    {avgs['analyzed_files']}")

    return avgs


def parse_codeql_sarif_py(sarif_path, print_report=True, show_lists=False):
    sarif_path = Path(sarif_path)
    data = json.loads(sarif_path.read_text(encoding="utf-8"))

    artifacts_seen = 0
    expected_uris = set()
    success_uris  = set()
    warning_uris  = set()
    syntax_uris   = set()
    analyzed_uris = set()

    runs = data.get("runs", []) or []
    for run in runs:
        artifacts = run.get("artifacts", []) or []
        artifacts_seen += len(artifacts)

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

        def _collect_uris(obj):
            """Estrae URI da locations e relatedLocations (se presenti)."""
            out = []
            for loc in (obj.get("locations", []) or []):
                phys = (loc.get("physicalLocation") or {})
                art  = (phys.get("artifactLocation") or {})
                uri  = _uri_from_artloc(art)
                if uri:
                    out.append(uri)
            for rloc in (obj.get("relatedLocations", []) or []):
                phys = (rloc.get("physicalLocation") or {})
                art  = (phys.get("artifactLocation") or {})
                uri  = _uri_from_artloc(art)
                if uri:
                    out.append(uri)
            return out

        diag_rule_ids = {
            "py/baseline/expected-extracted-files",
            "py/diagnostics/successfully-extracted-files",
            "py/diagnostics/extraction-warnings",
            "py/diagnostics/syntax-error",
            "py/diagnostic/database-quality",
        }
        for res in run.get("results", []) or []:
            rid = res.get("ruleId") or (res.get("rule") or {}).get("id")
            if rid in diag_rule_ids:
                continue
            for uri in _collect_uris(res):
                analyzed_uris.add(uri)

        for inv in run.get("invocations", []) or []:
            for tn in inv.get("toolExecutionNotifications", []) or []:
                desc_id = (tn.get("descriptor") or {}).get("id") or tn.get("id") or tn.get("name") or ""
                dest = None
                if desc_id == "py/baseline/expected-extracted-files":
                    dest = expected_uris
                elif desc_id == "py/diagnostics/successfully-extracted-files":
                    dest = success_uris
                elif desc_id == "py/diagnostics/extraction-warnings":
                    dest = warning_uris
                elif desc_id == "py/diagnostics/syntax-error":
                    dest = syntax_uris
                if dest is not None:
                    for uri in _collect_uris(tn):
                        dest.add(uri)

        diag_map = {
            "py/baseline/expected-extracted-files": expected_uris,
            "py/diagnostics/successfully-extracted-files": success_uris,
            "py/diagnostics/extraction-warnings": warning_uris,
            "py/diagnostics/syntax-error": syntax_uris,
        }
        for res in run.get("results", []) or []:
            rid = res.get("ruleId") or (res.get("rule") or {}).get("id")
            dest_set = diag_map.get(rid)
            if dest_set is not None:
                for uri in _collect_uris(res):
                    dest_set.add(uri)

        for notif in (run.get("tool", {}).get("driver", {}).get("notifications", []) or []):
            nid = notif.get("id") or notif.get("name") or ""
            dest = None
            if nid == "py/baseline/expected-extracted-files":
                dest = expected_uris
            elif nid == "py/diagnostics/successfully-extracted-files":
                dest = success_uris
            elif nid == "py/diagnostics/extraction-warnings":
                dest = warning_uris
            elif nid == "py/diagnostics/syntax-error":
                dest = syntax_uris
            if dest is not None:
                for uri in _collect_uris(notif):
                    dest.add(uri)

    files_expected = len(expected_uris)
    files_extracted = len(success_uris)
    files_not_extracted = max(0, files_expected - files_extracted)

    summary = {
        "artifacts_seen": artifacts_seen,
        "files_expected": files_expected,
        "files_extracted": files_extracted,
        "files_not_extracted": files_not_extracted,
        "extraction_warnings": len(warning_uris),
        "syntax_errors": len(syntax_uris),
        "analyzed_files": len(analyzed_uris),

        "expected_uris": sorted(expected_uris),
        "success_uris": sorted(success_uris),
        "warning_uris": sorted(warning_uris),
        "syntax_uris": sorted(syntax_uris),
        "analyzed_uris": sorted(analyzed_uris),
    }

    if print_report:
        print("== CodeQL SARIF – Python – Riepilogo ==")
        print(f"Artefatti registrati:                 {summary['artifacts_seen']}")
        print(f"File attesi (baseline):               {summary['files_expected']}")
        print(f"File estratti (nel DB):               {summary['files_extracted']}")
        print(f"File non estratti (non nel DB):       {summary['files_not_extracted']}")
        print(f"Warning di estrazione (.py):          {summary['extraction_warnings']}")
        print(f"Errori di sintassi (.py):             {summary['syntax_errors']}")
        print(f"File citati nei risultati (query):    {summary['analyzed_files']}")

        if show_lists:
            def _dump(title, items):
                print(f"\n-- {title} ({len(items)}) --")
                for u in items:
                    print(" ", u)

            _dump("Expected (baseline)", summary["expected_uris"])
            _dump("Successfully extracted", summary["success_uris"])
            _dump("Extraction warnings", summary["warning_uris"])
            _dump("Syntax errors", summary["syntax_uris"])
            _dump("Files con risultati (non diagnostica)", summary["analyzed_uris"])

    return summary


def parse_codeql_sarif_py_merged(sarif_a, sarif_b, sarif_c, print_report=True, rounding="nearest"):
    if "parse_codeql_sarif_py" not in globals():
        raise RuntimeError(
            "La funzione 'parse_codeql_sarif_py' deve essere definita nello scope."
        )

    def _iround(x: float) -> int:
        if rounding == "nearest":
            return int(round(x))
        elif rounding == "floor":
            return math.floor(x)
        elif rounding == "ceil":
            return math.ceil(x)
        else:
            raise ValueError("rounding deve essere 'nearest', 'floor' o 'ceil'.")

    numeric_keys = [
        "artifacts_seen",
        "files_expected",
        "files_extracted",
        "files_not_extracted",
        "extraction_warnings",
        "syntax_errors",
        "analyzed_files",
    ]

    sums = {k: 0 for k in numeric_keys}
    for path in (sarif_a, sarif_b, sarif_c):
        summary = parse_codeql_sarif_py(path, print_report=False, show_lists=False)
        for k in numeric_keys:
            sums[k] += int(summary.get(k, 0))

    avgs = {k: _iround(sums[k] / 3.0) for k in numeric_keys}

    if print_report:
        print("== CodeQL SARIF – Medie su 3 file ==")
        print(f"Artefatti registrati (media):         {avgs['artifacts_seen']}")
        print(f"File attesi (baseline, media):        {avgs['files_expected']}")
        print(f"File estratti (DB, media):            {avgs['files_extracted']}")
        print(f"File non estratti (media):            {avgs['files_not_extracted']}")
        print(f"Warning di estrazione (media):        {avgs['extraction_warnings']}")
        print(f"Errori di sintassi (media):           {avgs['syntax_errors']}")
        print(f"File citati nei risultati (media):    {avgs['analyzed_files']}")

    return avgs


###################################################################################################################


model_name = "qwen"
sample = 1


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


command_set_sample_baseline_analysis_py = [
    # Databases folder creation (if not exists)
    r'[ -d "CodeQL/Databases" ] || mkdir -p "CodeQL/Databases"',

    # Database creation starting from code
    f'codeql database create CodeQL/Databases/python_baseline_db --language=python --source-root=samples_generated_code/sample_{sample}/{model_name}/baseline_code_py --overwrite',

    # Query update and configuration
    r'codeql pack download codeql/python-queries@1.6.0',

    # Database complete analysis for CWE match
    f'codeql database analyze CodeQL/Databases/python_baseline_db --format=sarifv2.1.0 --output=samples_results/sample_{sample}/{model_name}/json/results_py_baseline.sarif.json codeql/python-queries@1.6.0 --warnings=hide --rerun --sarif-add-query-help',

    # Database analysis using downloaded query pack
    f'codeql database analyze CodeQL/Databases/python_baseline_db --format=csv --output=samples_results/sample_{sample}/{model_name}/baseline/results_py_baseline.csv codeql/python-queries@1.6.0 --warnings=hide --rerun'
]


command_set_result_analysis_py = [
    # Databases folder creation (if not exists)
    r'[ -d "CodeQL/Databases" ] || mkdir -p "CodeQL/Databases"',

    # Database creation starting from code
    f'codeql database create CodeQL/Databases/python_analysis_db --language=python --source-root=generated_code/{model_name}/generated_code_py --overwrite',

    # Query download and installation for C/C++, Python and Java
    r'codeql pack download codeql/python-queries@1.6.0',

    # Database complete analysis for CWE match
    f'codeql database analyze CodeQL/Databases/python_analysis_db --format=sarifv2.1.0 --output=results/{model_name}/json/results_py.sarif.json codeql/python-queries@1.6.0 --warnings=hide --rerun --sarif-add-query-help',

    # Database analysis using downloaded query pack
    f'codeql database analyze CodeQL/Databases/python_analysis_db --format=csv --output=results/{model_name}/permutations/results_py.csv codeql/python-queries@1.6.0 --warnings=hide --rerun'
]

command_set_sample_result_analysis_py = [
    # Databases folder creation (if not exists)
    r'[ -d "CodeQL/Databases" ] || mkdir -p "CodeQL/Databases"',

    # Database creation starting from code
    f'codeql database create CodeQL/Databases/python_analysis_db --language=python --source-root=samples_generated_code/sample_{sample}/{model_name}/generated_code_py --overwrite',

    # Query update and configuration
    r'codeql pack download codeql/python-queries@1.6.0',

    # Database complete analysis for CWE match
    f'codeql database analyze CodeQL/Databases/python_analysis_db --format=sarifv2.1.0 --output=samples_results/sample_{sample}/{model_name}/json/results_py.sarif.json codeql/python-queries@1.6.0 --warnings=hide --rerun --sarif-add-query-help',

    # Database analysis using downloaded query pack
    f'codeql database analyze CodeQL/Databases/python_analysis_db --format=csv --output=samples_results/sample_{sample}/{model_name}/permutations/results_py.csv codeql/python-queries@1.6.0 --warnings=hide --rerun'
]


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

command_set_sample_baseline_analysis_java = [
    # Databases folder creation (if not exists)
    r'[ -d "CodeQL/Databases" ] || mkdir -p "CodeQL/Databases"',

    # Database creation starting from code
    f'codeql database create CodeQL/Databases/java_baseline_db --language=java --source-root=samples_generated_code/sample_{sample}/{model_name}/baseline_code_java_formatted --command="mvn clean compile --fail-never" --overwrite',

    # Query update and configuration
    r'codeql pack download codeql/python-queries@1.6.0',

    # Database complete analysis for CWE match
    f'codeql database analyze CodeQL/Databases/java_baseline_db --format=sarifv2.1.0 --output=samples_results/sample_{sample}/{model_name}/json/results_java_baseline.sarif.json codeql/java-queries@1.5.2 --warnings=hide --rerun --sarif-add-query-help',

    # Database analysis using downloaded query pack
    f'codeql database analyze CodeQL/Databases/java_baseline_db --format=csv --output=samples_results/sample_{sample}/{model_name}/baseline/results_java_baseline.csv codeql/java-queries@1.5.2 --warnings=hide --rerun'
]


command_set_result_analysis_java = [
    # Databases folder creation (if not exists)
    r'[ -d "CodeQL/Databases" ] || mkdir -p "CodeQL/Databases"',

    # Database creation starting from code
    f'codeql database create CodeQL/Databases/java_analysis_db --language=java --source-root=generated_code/{model_name}/generated_code_java_formatted --command="mvn clean compile --fail-never" --overwrite',

    # Query download and installation for Java
    r'codeql pack download codeql/java-queries@1.5.2',

    # Database complete analysis for CWE match
    f'codeql database analyze CodeQL/Databases/java_analysis_db --format=sarifv2.1.0 --output=results/{model_name}/json/results_java.sarif.json codeql/java-queries@1.5.2 --warnings=hide --rerun --sarif-add-query-help',

    # Database analysis using downloaded query pack
    f'codeql database analyze CodeQL/Databases/java_analysis_db --format=csv --output=results/{model_name}/permutations/results_java.csv codeql/java-queries@1.5.2 --warnings=hide --rerun'
]


command_set_sample_result_analysis_java = [
    # Databases folder creation (if not exists)
    r'[ -d "CodeQL/Databases" ] || mkdir -p "CodeQL/Databases"',

    # Database creation starting from code
    f'codeql database create CodeQL/Databases/java_analysis_db --language=java --source-root=samples_generated_code/sample_{sample}/{model_name}/generated_code_java_formatted --command="mvn clean compile --fail-never" --overwrite',

    # Query download and installation for Java
    r'codeql pack download codeql/java-queries@1.5.2',

    # Database complete analysis for CWE match
    f'codeql database analyze CodeQL/Databases/java_analysis_db --format=sarifv2.1.0 --output=samples_results/sample_{sample}/{model_name}/json/results_java.sarif.json codeql/java-queries@1.5.2 --warnings=hide --rerun --sarif-add-query-help',

    # Database analysis using downloaded query pack
    f'codeql database analyze CodeQL/Databases/java_analysis_db --format=csv --output=samples_results/sample_{sample}/{model_name}/permutations/results_java.csv codeql/java-queries@1.5.2 --warnings=hide --rerun'
]


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


command_set_sample_baseline_analysis_c = [
    # Databases folder creation (if not exists)
    r'[ -d "CodeQL/Databases" ] || mkdir -p "CodeQL/Databases"',

    # Database creation starting from code
    f'codeql database create CodeQL/Databases/c_baseline_db --language=c --source-root=samples_generated_code/sample_{sample}/{model_name}/baseline_code_c_formatted --command="make -k" --overwrite',

    # Query update and configuration
    r'codeql pack download codeql/cpp-queries@1.4.3',

    # Database complete analysis for CWE match
    f'codeql database analyze CodeQL/Databases/c_baseline_db --format=sarifv2.1.0 --output=samples_results/sample_{sample}/{model_name}/json/results_c_baseline.sarif.json codeql/cpp-queries@1.4.3 --warnings=hide --rerun --sarif-add-query-help',

    # Database analysis using downloaded query pack
    f'codeql database analyze CodeQL/Databases/c_baseline_db --format=csv --output=samples_results/sample_{sample}/{model_name}/baseline/results_c_baseline.csv codeql/cpp-queries@1.4.3 --warnings=hide --rerun'
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


command_set_sample_result_analysis_c = [
    # Databases folder creation (if not exists)
    r'[ -d "CodeQL/Databases" ] || mkdir -p "CodeQL/Databases"',

    # Database creation starting from code
    f'codeql database create CodeQL/Databases/c_analysis_db --language=c --source-root=samples_generated_code/sample_{sample}/{model_name}/generated_code_c_formatted --command="make -k" --overwrite',

    # Query download and installation for C
    r'codeql pack download codeql/cpp-queries@1.4.3',

    # Database complete analysis for CWE match
    f'codeql database analyze CodeQL/Databases/c_analysis_db --format=sarifv2.1.0 --output=samples_results/sample_{sample}/{model_name}/json/results_c.sarif.json codeql/cpp-queries@1.4.3 --warnings=hide --rerun --sarif-add-query-help',

    # Database analysis using downloaded query pack
    f'codeql database analyze CodeQL/Databases/c_analysis_db --format=csv --output=samples_results/sample_{sample}/{model_name}/permutations/results_c.csv codeql/cpp-queries@1.4.3 --warnings=hide --rerun'
]



class SecurityAnalysis:
    def __init__(self, commands):
        run_sh_commands(commands)


class PythonPreprocessing:
    def __init__(self, folder):
        self.folder = folder
        count_short_files(folder)
        collect_python_imports(folder)


class JavaPreprocessing:
    def __init__(self, folder1, folder2, nested):
        self.folder1 = folder1
        self.folder2 = folder2
        self.nested = nested

        create_formatted_folder(folder1, folder2)

        count_short_files(folder2)
        extract_unique_java_imports(folder2, exclude_java_standard=True)

        create_maven_structure(folder2, nested=nested, with_imports=True)
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
            "stdbool.h": set(),
            "stdint.h": set(),
            "tgmath.h": set(),
            "stdalign.h": set(),
            "stdatomic.h": set(),
            "stdnoreturn.h": set(),
        }

        create_formatted_folder(folder1, folder2)

        count_short_files(folder2)

        find_unique_includes(folder2, STANDARD_C_FUNCTIONS, True)

        build_c_project(folder2, nested, mode="auto")


class CodeAnalysisOutcome:
    def __init__(self):
        print("C Code Analysis Outcome:")
        parse_codeql_sarif_c(f"results/{model_name}/json/results_c_baseline.sarif.json")
        parse_codeql_sarif_c(f"results/{model_name}/json/results_c.sarif.json")
        print("\n----------------------------------------------------------------\n")
        print("Java Code Analysis Outcome:")
        parse_codeql_sarif_java(f"results/{model_name}/json/results_java_baseline.sarif.json")
        parse_codeql_sarif_java(f"results/{model_name}/json/results_java.sarif.json")
        print("\n----------------------------------------------------------------\n")
        print("Python Code Analysis Outcome:")
        parse_codeql_sarif_py(f"results/{model_name}/json/results_py_baseline.sarif.json")
        parse_codeql_sarif_py(f"results/{model_name}/json/results_py.sarif.json")
        print("\n----------------------------------------------------------------\n")


class SampleCodeAnalysisOutcome:
    def __init__(self):
        print("C Sample Code Analysis Outcome:")
        parse_codeql_sarif_c_merged(f"samples_results/sample_1/{model_name}/json/results_c_baseline.sarif.json",
                                    f"samples_results/sample_2/{model_name}/json/results_c_baseline.sarif.json",
                                    f"samples_results/sample_3/{model_name}/json/results_c_baseline.sarif.json")
        parse_codeql_sarif_c_merged(f"samples_results/sample_1/{model_name}/json/results_c.sarif.json",
                                    f"samples_results/sample_2/{model_name}/json/results_c.sarif.json",
                                    f"samples_results/sample_3/{model_name}/json/results_c.sarif.json")
        print("\n----------------------------------------------------------------\n")

        print("Java Sample Code Analysis Outcome:")
        parse_codeql_sarif_java_merged(f"samples_results/sample_1/{model_name}/json/results_java_baseline.sarif.json",
                                       f"samples_results/sample_2/{model_name}/json/results_java_baseline.sarif.json",
                                       f"samples_results/sample_3/{model_name}/json/results_java_baseline.sarif.json")
        parse_codeql_sarif_java_merged(f"samples_results/sample_1/{model_name}/json/results_java.sarif.json",
                                       f"samples_results/sample_2/{model_name}/json/results_java.sarif.json",
                                       f"samples_results/sample_3/{model_name}/json/results_java.sarif.json")
        print("\n----------------------------------------------------------------\n")

        print("Python Sample Code Analysis Outcome:")
        parse_codeql_sarif_py_merged(f"samples_results/sample_1/{model_name}/json/results_py_baseline.sarif.json",
                                     f"samples_results/sample_2/{model_name}/json/results_py_baseline.sarif.json",
                                     f"samples_results/sample_3/{model_name}/json/results_py_baseline.sarif.json")
        parse_codeql_sarif_py_merged(f"samples_results/sample_1/{model_name}/json/results_py.sarif.json",
                                     f"samples_results/sample_2/{model_name}/json/results_py.sarif.json",
                                     f"samples_results/sample_3/{model_name}/json/results_py.sarif.json")
        print("\n----------------------------------------------------------------\n")



python_baseline_folder = f"generated_code/{model_name}/baseline_code_py"
python_folder = f"generated_code/{model_name}/generated_code_py"

java_baseline_folder = f"generated_code/{model_name}/baseline_code_java"
java_baseline_folder_formatted = f"generated_code/{model_name}/baseline_code_java_formatted"
java_folder = f"generated_code/{model_name}/generated_code_java"
java_folder_formatted = f"generated_code/{model_name}/generated_code_java_formatted"

c_baseline_folder = f"generated_code/{model_name}/baseline_code_c"
c_baseline_folder_formatted = f"generated_code/{model_name}/baseline_code_c_formatted"
c_folder = f"generated_code/{model_name}/generated_code_c"
c_folder_formatted = f"generated_code/{model_name}/generated_code_c_formatted"

samples_baseline_csv = f"samples/baseline_sample_{sample}.csv"
samples_permutations_folder = f"samples/permutations_sample_{sample}"
samples_baseline_code_py = f"samples_generated_code/sample_{sample}/{model_name}/baseline_code_py"
samples_permutations_code_py = f"samples_generated_code/sample_{sample}/{model_name}/generated_code_py"

samples_baseline_code_java = f"samples_generated_code/sample_{sample}/{model_name}/baseline_code_java"
samples_baseline_code_java_formatted = f"samples_generated_code/sample_{sample}/{model_name}/baseline_code_java_formatted"
samples_permutations_code_java = f"samples_generated_code/sample_{sample}/{model_name}/generated_code_java"
samples_permutations_code_java_formatted = f"samples_generated_code/sample_{sample}/{model_name}/generated_code_java_formatted"


samples_baseline_code_c = f"samples_generated_code/sample_{sample}/{model_name}/baseline_code_c"
samples_baseline_code_c_formatted = f"samples_generated_code/sample_{sample}/{model_name}/baseline_code_c_formatted"
samples_permutations_code_c = f"samples_generated_code/sample_{sample}/{model_name}/generated_code_c"
samples_permutations_code_c_formatted = f"samples_generated_code/sample_{sample}/{model_name}/generated_code_c_formatted"




PythonPreprocessing(python_baseline_folder)
SecurityAnalysis(command_set_baseline_analysis_py)
PythonPreprocessing(python_folder)
SecurityAnalysis(command_set_result_analysis_py)


JavaPreprocessing(java_baseline_folder, java_baseline_folder_formatted, nested=False)
SecurityAnalysis(command_set_baseline_analysis_java)
JavaPreprocessing(java_folder, java_folder_formatted, nested=True)
SecurityAnalysis(command_set_result_analysis_java)

CPreprocessing(c_baseline_folder, c_baseline_folder_formatted, nested=False)
SecurityAnalysis(command_set_baseline_analysis_c)
CPreprocessing(c_folder, c_folder_formatted, nested=True)
SecurityAnalysis(command_set_result_analysis_c)

CodeAnalysisOutcome()



PythonPreprocessing(samples_baseline_code_py)
PythonPreprocessing(samples_permutations_code_py)
SecurityAnalysis(command_set_sample_baseline_analysis_py)
SecurityAnalysis(command_set_sample_result_analysis_py)

JavaPreprocessing(samples_baseline_code_java, samples_baseline_code_java_formatted, nested=False)
SecurityAnalysis(command_set_sample_baseline_analysis_java)
JavaPreprocessing(samples_permutations_code_java, samples_permutations_code_java_formatted, nested=True)
SecurityAnalysis(command_set_sample_result_analysis_java)

CPreprocessing(samples_baseline_code_c, samples_baseline_code_c_formatted, nested=False)
SecurityAnalysis(command_set_sample_baseline_analysis_c)
CPreprocessing(samples_permutations_code_c, samples_permutations_code_c_formatted, nested=True)
SecurityAnalysis(command_set_sample_result_analysis_c)

SampleCodeAnalysisOutcome()
