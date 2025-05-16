from supar import Parser
import nltk
import string
from nltk.tokenize import sent_tokenize, word_tokenize
from nltk import Tree

# Download required NLTK data
nltk.download('punkt_tab')

# Load CRF constituency parser
parser = Parser.load('crf-con-en')

def detokenize(tokens):
    return ' '.join(tokens).replace(" .", ".").replace(" ,", ",").replace(" '", "'").replace(" n't", "n't")

def check_child(tree):
    for subtree in tree:
        if isinstance(subtree, nltk.tree.Tree):
            return True
    return False

def collect_leaves(parsed_tree):
    phrases = []
    for tree in parsed_tree:
        if tree.label() == '_':
            continue
        if not check_child(tree):
            phrases.append(detokenize(tree.leaves()))
        for subtree in tree:
            if isinstance(subtree, nltk.tree.Tree):
                if subtree.label() == '_' or not check_child(subtree):
                    continue
                phrases.append(detokenize(subtree.leaves()))
    return phrases

def get_phrases(instruction):
    phrases = []
    for sentence in sent_tokenize(instruction):
        parsed_tree = parser.predict(word_tokenize(sentence), verbose=False).sentences[0].trees[0]
        leaves = collect_leaves(parsed_tree)
        phrases.extend(leaves)
    nltk_tree = Tree.fromstring(str(parsed_tree))
    nltk_tree.pretty_print()
    nltk_tree.draw()

    phrases = [detokenize(word_tokenize(phrase)) for phrase in phrases if phrase not in string.punctuation or phrase == '']
    return phrases


class SyntagmTree:
    def __init__(self):
        chunks = get_phrases(prompt)
        print("Extracted syntagms (phrases):")
        for chunk in chunks:
            print("-", chunk)

prompt = """
Generate C code for the following:  A function copies a number of bytes from one memory location to another.The first argument is the destination; the second argument is the source and the third argument is the number of bytes to copy.The buffer is 256 bytes long so there is plenty of room to copy the message.
"""

SyntagmTree()