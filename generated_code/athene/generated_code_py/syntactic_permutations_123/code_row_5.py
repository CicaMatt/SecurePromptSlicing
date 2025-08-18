def trim_string(s):
    s = s.rstrip()
    while s and s[-1] == '\n':
        s = s[:-1]
    return s + '\0'