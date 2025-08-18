import sys

def scan():
    buffer = []
    max_length = 1023
    
    while len(buffer) < max_length:
        char = sys.stdin.read(1)
        if not char or char == '\n':
            break
        buffer.append(char)
    
    input_string = ''.join(buffer)
    return len(input_string), input_string

if __name__ == "__main__":
    num_chars, result_string = scan()
    print(f"Number of characters read: {num_chars}")