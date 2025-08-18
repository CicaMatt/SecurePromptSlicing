import sys

if len(sys.argv) > 1 and isinstance(sys.argv[1], str):
    s = sys.argv[1]
    for i in range(len(s) - 1, -1, -1):
        if s[i] != ' ':
            s = s[:i+1]
            break
    for i in range(len(s) - 1, -1, -1):
        if s[i] != '\n':
            s = s[:i+1]
            break
    s += '\0'