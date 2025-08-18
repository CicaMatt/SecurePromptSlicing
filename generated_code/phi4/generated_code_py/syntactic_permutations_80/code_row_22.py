import sys

def scan():
    buffer = []
    max_length = 1023
    for char in iter(lambda: sys.stdin.read(1), '\n'):
        if len(buffer) < max_length:
            buffer.append(char)
        else:
            break
    input_string = ''.join(buffer)
    print(f"Number of characters read: {len(input_string)}")
    return input_string

if __name__ == "__main__":
    scan()