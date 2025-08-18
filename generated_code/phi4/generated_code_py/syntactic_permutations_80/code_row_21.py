import sys

def scan():
    buffer = []
    for char in iter(lambda: sys.stdin.read(1), '\n'):
        if len(buffer) < 1023:
            buffer.append(char)
    return ''.join(buffer)

if __name__ == "__main__":
    input_string = scan()
    num_chars_read = len(input_string)
    print(num_chars_read)