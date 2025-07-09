import re

def scan(input):
    match = re.findall('\n', input)
    return len(match)