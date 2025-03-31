from supar import Parser
import nltk
import string
from nltk.tokenize import sent_tokenize, word_tokenize

# Download required NLTK data
nltk.download('punkt')

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
    phrases = [detokenize(word_tokenize(phrase)) for phrase in phrases if phrase not in string.punctuation or phrase == '']
    return phrases

# === Example Usage ===
if __name__ == "__main__":
    prompt = """
I am working on a swing application in which in which client has to access the html files locally stored in the machine but i want client should not access the html files directly so want to encrypt the entire folder of html files using java and in Java application i would write the hard code to decrypt the html files from encrypted folder. One more thing the updation should be possible in encrypted folder so that encrypted files may be merged in future on client side.

I have been stuck here and has no clues for my problem , any help for my problem is appreciated.
    """
    chunks = get_phrases(prompt)
    print("Extracted syntagms (phrases):")
    for chunk in chunks:
        print("-", chunk)