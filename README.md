# Secure Prompt Slicing

### Script descriptions:
- _syntagm_tree_generation_ <br>
Prompt syntagm tree generation
- _prompt_permutation_generation_ <br>
Generates all possible permutations out of a prompt and output a csv
- _permutation_testing_ <br>
Generates answers based on the csv generated earlier
- _security_analysis_ <br>
Analysis of test suites in _data_ folder for C, Java and Python
<br><br>


  
### Parser: [_crf-con-en_ (SuPar)](https://parser.readthedocs.io/en/stable/models/const.html?highlight=crf%20con%20en#supar.models.const.CRFConstituencyModel)
<br>


### Syntagm Component Explanation ([Penn Treebank II Standard](https://surdeanu.cs.arizona.edu/mihai/teaching/ista555-fall13/readings/PennTreebankConstituents.html))

#### Clause Level
- **S** — Simple declarative clause, i.e. one that is not introduced by a (possible empty) subordinating conjunction or a wh-word and that does not exhibit subject-verb inversion
- **SBAR** — Clause introduced by a (possibly empty) subordinating conjunction

#### Phrase Level
- **PP** — Prepositional Phrase  
- **VP** — Verb Phrase  
- **NP** — Noun Phrase  
- **ADJP** — Adjective Phrase  
- **ADVP** — Adverb Phrase  
- **CONJP** — Conjunction Phrase

