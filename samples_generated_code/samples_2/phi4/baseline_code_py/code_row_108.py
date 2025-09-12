import sys

def scan():
    buffer = []
    max_length = 1023
    
    while True:
        char = sys.stdin.read(1)
        if not char or char == '\n':
            break
        buffer.append(char)
        if len(buffer) >= max_length:
            break

    return ''.join(buffer)

if __name__ == "__main__":
    result = scan()
    print(len(result))