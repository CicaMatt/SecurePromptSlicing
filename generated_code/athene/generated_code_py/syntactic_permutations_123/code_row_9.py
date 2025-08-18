import sys

def trim_string(s):
    if len(sys.argv) != 2:
        return None
    s = sys.argv[1]
    if not isinstance(s, str):
        return None
    for i in range(len(s)):
        if s[-i-1].isspace():
            s = s[:-i-1]
        else:
            break
    for i in range(len(s)):
        if s[-i-1] == '\n':
            s = s[:-i-1]
        else:
            break
    return s + '\0'

result = trim_string(sys.argv[1]) if len(sys.argv) == 2 else None
print(result)