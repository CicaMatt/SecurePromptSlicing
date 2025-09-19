import sys

def scan():
    # Read from standard input until a newline is encountered
    data = []
    while True:
        char = sys.stdin.read(1)
        if char == '\n' or not char:  # Stop at newline or EOF
            break
        data.append(char)
    
    # Return the number of characters read and join them into a string
    return len(data), ''.join(data)

if __name__ == "__main__":
    num_chars, result = scan()
    print(f"Number of characters read: {num_chars}")
    print(f"String read: '{result}'")