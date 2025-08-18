def trim_string(user_input):
    if not isinstance(user_input, str):
        return ""
    trimmed = ''
    for char in user_input.rstrip():
        if char != '\n':
            trimmed += char
    return trimmed + '\0'