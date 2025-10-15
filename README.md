# Secure Prompt Slicing

### Script descriptions:
- _syntagm_tree_generation_ <br>
Prompt syntagm tree generation
- _prompt_permutation_generation_ <br>
Generates all possible permutations out of a prompt and output a csv
- _permutations_code_generation <br>
Generates snippets based on the available permutations
- _security_analysis_ <br>
Code analysis for C, Java, Python
- _result_analysis_ <br>
Result analysis for a single programming language
- _result_comparison_ <br>
Result comparison over different programming languages
<br><br>


  
### Parser: [_crf-con-en_ (SuPar)](https://parser.readthedocs.io/en/stable/models/const.html?highlight=crf%20con%20en#supar.models.const.CRFConstituencyModel)

### Syntagm Component Explanation ([Penn Treebank II Standard](https://surdeanu.cs.arizona.edu/mihai/teaching/ista555-fall13/readings/PennTreebankConstituents.html))

#### Clause Level
- **S** — Simple declarative clause, i.e. one that is not introduced by a (possible empty) subordinating conjunction or a wh-word and that does not exhibit subject-verb inversion
- **SBAR** — Clause introduced by a (possibly empty) subordinating conjunction
- **SINV** — Inverted declarative sentence, i.e. one in which the subject follows the tensed verb or modal.

#### Phrase Level
- **PP** — Prepositional Phrase  
- **VP** — Verb Phrase  
- **NP** — Noun Phrase  
- **ADJP** — Adjective Phrase  
- **ADVP** — Adverb Phrase  
- **CONJP** — Conjunction Phrase
- **PRT** — Parenthetical
- **WHNP** — Wh-noun Phrase. Introduces a clause with an NP gap. May be null (containing the 0 complementizer) or lexical, containing some wh-word, e.g. who, which book, whose daughter, none of which, or how many leopards.
- **WHPP** — Wh-prepositional Phrase. Prepositional phrase containing a wh-noun phrase (such as of which or by whose authority) that either introduces a PP gap or is contained by a WHNP.
- **WHADJP** — Wh-adjective Phrase. Adjectival phrase containing a wh-adverb, as in how hot.
- **WHADVP** — ???
- **INTJ** — Interjection. Corresponds approximately to the part-of-speech tag UH.
- **QP** — Quantifier Phrase (i.e. complex measure/amount phrase); used within NP.
- **LST** — List marker. Includes surrounding punctuation.
- **FRAG** — Fragment
<br><br>

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
<br><br>



### Baseline Comparison Labels
- **CWE** — Considered CWE scenario
- **Base** — Vulnerable permutation snippets
- **Result** — Vulnerable baseline snippets
- **Frequency** — Percentage of vulnerable baseline snippets over vulnerable permutation snippets


### Permutations Comparison Labels
- **CWE** — Considered CWE scenario
- **Base** — Total permutations snippets
- **Result** — Total vulnerable snippets
- **Frequency** — Percentage of vulnerable snippets over total snippets


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












<div align="center">
  
  <h2 align="center">The Language of Security: Prompt Language and Its Influence on the Security of LLM-Generated Code</h2>

  <p align="center">
    A benchmark study on the impact of Meta-Prompting on the security and quality of artificially generated code.
  </p>
</div>

## About The Project
This project conduct a study on the impact of low-level constituents in the generation of secure code through LLM, by creating permutation of certain prompt and analyzing the impact of the removal constituent on security.

## Repository Contents
### _LLMSecEvalDataset.csv_
Baseline dataset used for the experiment

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
- _prompt_permutation_generation.py_: Generates all possible permutations out of a prompt and output a csv
- _permutations_code_generation.py_: Generates snippets based on the available permutations
- _security_analysis.py__: Code analysis for C, Java, Python
- _result_analysis.py_: Result analysis for a single programming language
- _result_comparison.py_: Result comparison over different programming languages
<br><br>



### _prompting_
Contains all the necessary scripts needed to prompt ChatGPT, Gemini and DeepSeek. In order for those script to work properly, all the API keys needs to be stored in the OS environment variables.

### _env_
Contains the .yaml file needed to replicate the environment.



## Getting Started

### Prerequisites
Python 3.12

### Installation

1. Install Dependencies:
   ```sh
   conda env create -f env.yaml
   ```
   
### How to use


   






