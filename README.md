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


