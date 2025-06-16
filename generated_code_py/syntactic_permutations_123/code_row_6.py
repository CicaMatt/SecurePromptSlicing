import re

def trim_trailing_whitespaces(string):
    return re.sub(r'\s+$', '', string)

def trim_newline(string):
    return re.sub(r'[\n]+', '', string)

def null_terminate(string):
    if not string.endswith('\0'):
        return string + '\0'