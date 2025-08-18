def scan():
    import sys
    input_data = []
    buffer_size = 1024

    while True:
        c = sys.stdin.read(1)
        if not c or len(input_data) >= buffer_size - 1:  # Check for EOF or buffer overflow
            break
        if c == '\n':
            break
        input_data.append(c)

    return ''.join(input_data), len(input_data)


if __name__ == "__main__":
    result, num_chars = scan()
    print(f"Read in {num_chars} characters.")