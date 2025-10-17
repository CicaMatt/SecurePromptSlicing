# The Language of Security: Prompt Language and Its Influence on the Security of LLM-Generated Code</h2>


## Repository Contents
### _LLMSecEvalDataset.csv_
Baseline dataset used for the experiment

### _env_
Contains the .yaml file needed to replicate the environment.

### _permutations_
Contains all the permutations produced with the _crf_con_en_ parser starting from the _LLMSecEval_ dataset

### _generated_code_
Contains all the generated code for the experiment across all languages and LLMs

### _CodeQL_
Contains all the databases for each CodeQL analysis run

### _results_
Contains all the csv files representing the several analysis steps employed

### _samples_
Contains all the sample data from which the experimental sample run has been started

### _samples_generated_code_
Contains all the generated code starting from the prompt of the sample set of data

### _samples_results_
Contains all the csv files related to the results of the sample experimental run

### _scripts_
Contains all the necessary scripts needed to perform the experiment:
- _syntagm_tree_generation.py_: Prompt syntagm tree generation
- _prompt_permutation_generation.py_: Generates all possible permutations out of a prompt set
- _permutations_code_generation.py_: Generates snippets based on the available permutations
- _security_analysis.py__: Code analysis for C, Java, Python through out compilation pipeline and CodeQL analysis
- _result_analysis.py_: Result analysis for the main experiment based on the CodeQL reports
- _samples_analysis.py_: Sample analysis for the main experiment based on the CodeQL reports

<br><br>



## Getting Started

### Prerequisites
Python 3.12\
Conda (preferred)

### Installation

1. Install project dependencies:
   ```sh
   conda env create -f env.yaml
   ```

2. Install [CodeQL](https://docs.github.com/en/code-security/codeql-cli/getting-started-with-the-codeql-cli/setting-up-the-codeql-cli)
<br><br>

3. Install C dependencies:
```
curl
httpd
json-c
libarchive
libmicrohttpd
libpq
libtar
libyaml
libzip
mongoose
mysql-client
openssl
pcre
sqlite
unixodbc
```


4. Install Java dependencies (the pom.xml with those dependencies is already configured in _security_analysis.py_):
```
com.google.code.gson:gson:2.10.1
com.konghq:unirest-java:3.13.6
com.mysql:mysql-connector-j:8.0.33
commons-codec:commons-codec:1.16.0
org.apache.commons:commons-compress:1.25.0
commons-fileupload:commons-fileupload:1.5
commons-io:commons-io:2.15.1
org.apache.httpcomponents:httpclient:4.5.14
org.springframework.boot:spring-boot-starter-web:3.2.4
org.springframework.boot:spring-boot-starter-thymeleaf:3.2.4
org.yaml:snakeyaml:2.4
com.sparkjava:spark-core:2.9.4
com.sparkjava:spark-template-freemarker:2.7.1
com.auth0:java-jwt:4.4.0
com.fasterxml.jackson.core:jackson-databind:2.17.1
com.fasterxml.jackson.dataformat:jackson-dataformat-yaml:2.17.1
io.javalin:javalin:5.6.3
jakarta.servlet:jakarta.servlet-api:6.0.0   
com.itextpdf:itextpdf:5.5.13.3
junit:junit:4.13.2                          
org.mongodb.morphia:morphia:1.3.2
org.mongodb:mongodb-driver-sync:4.11.1
com.amazonaws:aws-lambda-java-core:1.2.3
com.amazonaws:aws-lambda-java-events:3.11.0
org.mindrot:jbcrypt:0.4
io.github.cdimascio:dotenv-java:3.0.0
org.apache.commons:commons-lang3:3.14.0
com.google.appengine:appengine-api-1.0-sdk:1.9.88
org.apache.velocity:velocity:1.7
com.fasterxml.jackson.core:jackson-core:2.17.1
org.thymeleaf:thymeleaf:3.1.2.RELEASE
commons-validator:commons-validator:1.8.0
org.sql2o:sql2o:1.6.0
ch.qos.logback:logback-classic:1.4.14
com.sparkjava:spark-template-thymeleaf:2.7.1
org.json:json:20240303
org.antlr:ST4:4.3.4
com.sparkjava:spark-template-handlebars:2.7.1
com.sparkjava:spark-template-mustache:2.7.1
com.sparkjava:spark-template-velocity:2.7.1
org.springframework.session:spring-session-core:3.2.3
org.springframework.session:spring-session-data-redis:3.2.3
org.springframework.session:spring-session-jdbc:3.2.3
jakarta.ws.rs:jakarta.ws.rs-api:3.1.0
org.glassfish.jersey.core:jersey-server:3.1.6
org.python:jython-standalone:2.7.4
com.github.spullara.mustache.java:compiler:0.9.10
com.zaxxer:HikariCP:5.1.0
org.freemarker:freemarker:2.3.32
io.github.classgraph:classgraph:4.8.172
io.jsonwebtoken:jjwt-api:0.12.6
io.jsonwebtoken:jjwt-impl:0.12.6            
io.jsonwebtoken:jjwt-jackson:0.12.6        
io.vertx:vertx-core:4.5.8
io.vertx:vertx-web:4.5.8
io.vertx:vertx-pg-client:4.5.8
commons-dbutils:commons-dbutils:1.8.1
org.apache.pdfbox:pdfbox:2.0.31
com.h2database:h2:2.2.224                   
org.jetbrains:annotations:24.1.0
org.glassfish.jersey.containers:jersey-container-grizzly2-http:3.1.6
org.glassfish.jersey.containers:jersey-container-jetty-http:3.1.6
org.glassfish.jersey.media:jersey-media-json-jackson:3.1.6
org.glassfish.jersey.ext:jersey-mvc-jsp:3.1.6
org.springframework.security:spring-security-crypto:6.2.4
org.apache.tomcat:tomcat-jdbc:10.1.24
javax.xml.bind:jaxb-api:2.3.1
org.glassfish.jaxb:jaxb-runtime:2.3.8
```

5. Install Python dependencies:
```
bcrypt
flask
flask-sqlalchemy
jinja2
mysqlclient      
numpy
opencv-python               
pandas
pillow                      
psycopg2-binary             
pyYAML                     
pymongo
sqlalchemy
validators
werkzeug
```

<br>

   
## How to replicate

To replicate the experiment, the following scripts must be run:
- _prompt_permutation_generation.py_:\
Produces all the permutations for the snippets available in the _LLMSecEvalDataset.csv_ (taken from the _Manually-fixed NL Prompt_ column). Moreover, this script will also create the sampled dataset under the _sample_ folder. 
- _permutations_code_generation.py_:\
Produces all the code snippets starting from the defined LLM and language (configuring them explicitly through the _model_identifier_, _model_name_, _language_ and _identifier_ variables for each run), for both the main and the sample experiment (for the latter, also the _sample_folder_id_ variable must be set).
- _security_analysis.py__:\
Setups the compilation pipelines and analyze the generated code snippets, based on the specified model and sample (defined respectively through the _model_ and _sample_ variables), producing the related csv and json reports for the baseline and permutations set (respectively under the results/_model_name_/baseline and the results/_model_name_/permutations folders). The CodeQL query packs will be automatically installed. 
- _result_analysis.py_:\
Performs all the analysis steps for the main experiment, produces the result csvs and prints the remaining information on console, based on the specified model and language (defined through the _model_name_, _language_ and _language_id_ variables).
- _samples_analysis.py_:\
Performs all the analysis steps for the sample experiment, produces the result csvs and prints the remaining information on console, based on the specified model and language (defined through the ___model_name_, _language_ and _language_id_ variables).

<br>

## Useful Info

### Syntactical Parser: [_crf-con-en_ (SuPar)](https://parser.readthedocs.io/en/stable/models/const.html?highlight=crf%20con%20en#supar.models.const.CRFConstituencyModel)

### Phrasing Standard: ([Penn Treebank II Standard](https://surdeanu.cs.arizona.edu/mihai/teaching/ista555-fall13/readings/PennTreebankConstituents.html))

<br>

## CSV Labels Explanation

### Results CSV Labels
- **Name** — Vulnerability name (from CodeQL query)
- **Description** — Vulnerability description (from CodeQL query)
- **Severity** — Vulnerability severity
- **Message** — Vulnerability message (from CodeQL query)
- **Path** — Path of analyzed snippet
- **StartLine** — Vulnerability start line
- **StartColumn** — Vulnerability start column
- **EndLine** — Vulnerability end line
- **EndColumn** — Vulnerability end column
- **Dataset ID** — ID of related prompt (based on LLMSecEval dataset)
- **Prompt ID** — Prompt ID of related prompt (based on LLMSecEval dataset)
- **CWE ID** — CWE-ID of considered vulnerability
- **Sliced Prompt** — Sliced prompt used to produce the related snippet
- **Original Sentence** — Original prompt
- **Removed part** — Removed part from original prompt
- **Sentence Index** — Index of the sentence from which the syntagm has been removed
- **Syntagm Type** — Type of the removed syntagm from the original prompt
- **Granularity** — Granularity of the removed syntagm
- **Resulting prompt** — Resulting prompt from the slicing operation

### Single Metrics Comparison Labels
- **Category** — Considered metric category
- **Value** — Considered metric value
- **Base** — Total values over permutation snippets
- **Result** — Total values over vulnerable permutation snippets
- **Frequency** — Percentage of vulnerable permutation snippets over total permutation snippets

### Combined Metrics Comparison Labels
- **Combination** — Considered combination of metrics
- **Features** — Number of considered metrics
- **Granularity** — Value of _Granularity_ metric
- **Sentence Index** — Value of _Sentence Index_ metric
- **Syntagm Type** — Value of _Syntagm Type_ metric
- **Base** — Total values over permutation snippets
- **Result** — Total values over vulnerable permutation snippets
- **Frequency** — Percentage of vulnerable permutation snippets over total permutation snippets
