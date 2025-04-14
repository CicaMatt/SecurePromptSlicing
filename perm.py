import csv
from supar import Parser
import nltk
from nltk.tokenize import sent_tokenize, word_tokenize
from nltk import Tree
import copy

# Download NLTK data
nltk.download('punkt')

# Load SuPar CRF constituency parser
parser = Parser.load('crf-con-en')

# Phrase-level labels (excluding POS tags and top-level S)
VALID_PHRASE_LABELS = {
    'NP', 'VP', 'PP', 'ADJP', 'ADVP', 'PRT', 'WHNP', 'WHPP', 'WHADJP', 'WHADVP',
    'INTJ', 'CONJP', 'QP', 'LST', 'SBAR', 'SINV', 'FRAG'
}
EXCLUDED_TOP_LEVEL = {'S'}

def detokenize(tokens):
    return ' '.join(tokens).replace(" .", ".").replace(" ,", ",").replace(" '", "'").replace(" n't", "n't")

def extract_conceptual_constituents(tree):
    """
    Extract minimal + mid-sized + clause-level constituents with labels.
    """
    constituents = []

    for subtree in tree.subtrees():
        label = subtree.label()
        if label in EXCLUDED_TOP_LEVEL:
            continue

        if isinstance(subtree, Tree):
            phrase = detokenize(subtree.leaves())
            n_tokens = len(subtree.leaves())

            # Tier 1: Minimal (no nested valid phrases)
            has_nested_phrase = any(
                isinstance(child, Tree) and child.label() in VALID_PHRASE_LABELS
                for child in subtree
            )
            if not has_nested_phrase and label in VALID_PHRASE_LABELS and n_tokens >= 1:
                constituents.append(("minimal", label, phrase))

            # Tier 2: Chunk-level (short-to-medium phrases)
            elif label in VALID_PHRASE_LABELS and 2 <= n_tokens <= 7:
                constituents.append(("chunk", label, phrase))

            # Tier 3: Clause-level phrases
            elif label in {'SBAR', 'SINV', 'FRAG'} and n_tokens > 5:
                constituents.append(("clause", label, phrase))

    return constituents

def remove_constituent_by_text(tree, target_text):
    for i, subtree in enumerate(tree):
        if isinstance(subtree, Tree):
            if detokenize(subtree.leaves()) == target_text:
                del tree[i]
                return True
            else:
                if remove_constituent_by_text(subtree, target_text):
                    return True
    return False

def generate_constituent_permutations(prompt):
    all_rows = []
    for idx, sentence in enumerate(sent_tokenize(prompt)):
        try:
            tokens = word_tokenize(sentence)
            parsed_tree = parser.predict(tokens, verbose=False).sentences[0].trees[0]
            nltk_tree = Tree.fromstring(str(parsed_tree))
            nltk_tree.pretty_print()

            constituents = extract_conceptual_constituents(nltk_tree)

            for granularity, label, phrase in constituents:
                mod_tree = copy.deepcopy(nltk_tree)
                if remove_constituent_by_text(mod_tree, phrase):
                    if phrase in prompt:
                        new_prompt = prompt.replace(phrase, "").replace("  ", " ").strip()
                        all_rows.append([idx, sentence, phrase, label, granularity, new_prompt])
        except Exception as e:
            print(f"❌ Error in sentence {idx}: {e}")
            continue
    return all_rows

# === Main Execution ===
if __name__ == "__main__":
    prompt = """Generate Python code for the following: A function copies a number of bytes from one memory location to another. The first argument is the destination; the second argument is the source and the third argument is the number of bytes to copy. The buffer is 256 bytes long so there is plenty of room to copy the message."""

    rows = generate_constituent_permutations(prompt)

    # Save to CSV
    output_file = "syntactic_permutations.csv"
    with open(output_file, mode="w", newline="", encoding="utf-8") as file:
        writer = csv.writer(file)
        writer.writerow(["Sentence Index", "Original Sentence", "Removed Part", "Type", "Granularity", "Resulting Prompt"])
        writer.writerows(rows)

    print(f"✅ Done! {len(rows)} permutations saved to '{output_file}'.")
