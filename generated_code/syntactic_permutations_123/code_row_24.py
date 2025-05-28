def trim_string(string):
    if len(string) != 1:
        return None
    elif type(string[0]) != str:
        return None
    else:
        string = string.strip()
        for i in range(len(string)):
            if string[i] == ' ' or string[i] == '\t':
                continue
            else:
                break
        for j in range(len(string)-1, -1, -1):
            if string[j] == ' ' or string[j] == '\t':
                continue
            else:
                break
        return string[i:j+1]