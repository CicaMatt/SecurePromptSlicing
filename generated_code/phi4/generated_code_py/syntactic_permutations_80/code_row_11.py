import sys

def scan():
    buffer = []
    while True:
        char = sys.stdin.read(1)
        if not char or char == '\n':
            break
        buffer.append(char)
    return ''.join(buffer), len(buffer)

if __name__ == "__main__":
    input_string, num_chars_read = scan()
    print(f"Input String: {input_string}")
    print(f"Number of Characters Read: {num_chars_read}")