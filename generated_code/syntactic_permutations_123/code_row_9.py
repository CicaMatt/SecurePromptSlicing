import re
s = "  This is a string."
if type(s) == str:
    for i in range(len(s)):
        if s[i] != ' ' and s[i] != '\t':
            break
    for j in range(len(s)-1, -1, -1):
        if s[j] != ' ' and s[j] != '\n':
            break
    s = re.sub(r"\s*$", "", s)
    s = re.sub(r"^\s*", "", s)