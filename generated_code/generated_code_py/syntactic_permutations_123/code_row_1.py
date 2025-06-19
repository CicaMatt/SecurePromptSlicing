def trim(s):
    if len(s) != 1:
        return s
    elif not isinstance(s[0], str):
        return s

    for i in range(len(s[0])):
        if s[0][i] != " ":
            break
    else:
        s = ""
        return s

    for j in range(len(s[0]) - 1, -1, -1):
        if s[0][j] != "\n":
            break
    else:
        s = ""
        return s

    return s[0][i : j + 1]