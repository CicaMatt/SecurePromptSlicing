import re

def trim_string(s):
    if not isinstance(s, str):
        raise ValueError("Argument must be a string")
    s = re.sub(r'^\s+', '', s)
    s = re.sub(r'\n\s*\n$', '\n', s)
    return s + '\0'
