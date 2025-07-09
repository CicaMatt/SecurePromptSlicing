def scan(format_str):
    buffer = ""
    while True:
        char = input()
        if char == '\n':
            break
        buffer += char
    return len(buffer)