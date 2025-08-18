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
    input_string, num_read = scan()
    print(f"Read {num_read} characters: {input_string}")