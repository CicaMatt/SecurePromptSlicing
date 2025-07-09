import re
def read_txt(filepath):
    with open(filepath, 'r') as f:
        text = f.read()
    return text