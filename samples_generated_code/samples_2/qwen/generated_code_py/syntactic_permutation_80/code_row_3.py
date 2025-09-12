import sys

def scan(buffer_size=1024):
    import io
    input_stream = io.StringIO(sys.stdin.read(buffer_size))
    buffer = []
    char_count = 0

    while True:
        char = input_stream.read(1)
        if not char or char == '\n':
            break
        if char_count < buffer_size - 1:  # Reserve space for the null terminator
            buffer.append(char)
            char_count += 1

    return char_count

# Example usage
if __name__ == "__main__":
    print(scan())