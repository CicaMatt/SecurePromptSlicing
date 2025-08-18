s = "  hello world! \n\n"
s = s.rstrip()
for i in range(len(s) - 1, -1, -1):
    if s[i] == '\n':
        s = s[:i]
    else:
        break
s += '\0'