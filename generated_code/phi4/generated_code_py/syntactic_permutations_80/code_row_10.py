import sys

def scan():
    buffer = bytearray()
    max_length = 1023
    while True:
        char = sys.stdin.read(1)
        if not char or char == '\n':
            break
        if len(buffer) < max_length:
            buffer.append(ord(char))
    return bytes(buffer).decode('utf-8'), len(buffer)

def main():
    input_string, num_chars_read = scan()
    print(f"Input String: {input_string}")
    print(f"Number of Characters Read: {num_chars_read}")

if __name__ == "__main__":
    main()