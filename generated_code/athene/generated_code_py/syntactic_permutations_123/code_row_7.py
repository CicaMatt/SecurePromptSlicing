def trim_string(s):
    s = s.rstrip()
    s = ''.join([c for c in s if c != '\n'])
    return s + '\0'

s = "  hello world  \n\n"
result = trim_string(s)
print(result[:-1])  # Exclude the null terminator when printing