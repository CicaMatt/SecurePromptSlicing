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
            
    # Return the number of characters read into the buffer, excluding the newline.
    return ''.join(buffer), len(buffer)

def main():
    input_string, num_chars = scan()
    print(f"Number of characters read: {num_chars}")
    print(f"Input string: {input_string}")

if __name__ == "__main__":
    main()