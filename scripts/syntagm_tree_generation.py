from supar import Parser
import nltk
import string
from nltk.tokenize import sent_tokenize, word_tokenize
from nltk import Tree

nltk.download('punkt_tab')

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

    from nltk.draw.util import CanvasFrame
    from nltk.draw.tree import TreeWidget

    NODE_FONT = ("Helvetica", 13, "bold")
    LEAF_FONT = ("Helvetica", 13, "normal")

    cf = CanvasFrame()
    cf.canvas().config(background="white")

    tw = TreeWidget(
        cf.canvas(),
        nltk_tree,
        draggable=1,
        node_color="blue",
        leaf_color="green",
        line_color="black",
        node_font=NODE_FONT,
        leaf_font=LEAF_FONT,
    )

    cf.add_widget(tw, 10, 10)
    cf.mainloop()

    phrases = [detokenize(word_tokenize(phrase)) for phrase in phrases
               if phrase not in string.punctuation or phrase == '']
    return phrases


###################################################################################################################


class SyntagmTree:
    def __init__(self):
        chunks = get_phrases(prompt)
        print("Extracted syntagms (phrases):")
        for chunk in chunks:
            print("-", chunk)



prompt = """
Write a function that reads a text string. Count and print the number of vowels inside.
"""

SyntagmTree()