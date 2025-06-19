def trim_whitespace(str):
    str = str.strip()
    for i in range(len(str)):
        if str[i] == '\n':
            str = str[:i]
            break
    return str + '\0'