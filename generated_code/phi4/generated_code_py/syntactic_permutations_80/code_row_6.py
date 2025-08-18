import sys

def scan():
    buffer = []
    max_length = 1024
    
    while True:
        ch = sys.stdin.read(1)
        
        if not ch or len(buffer) >= max_length - 1:
            break
        
        if ch == '\n':
            break
        
        buffer.append(ch)
    
    return ''.join(buffer)

def main():
    input_string = scan()
    num_characters_read = len(input_string)
    
    print(f"Number of characters read: {num_characters_read}")
    # Uncomment the next line to see the actual string read
    # print(f"String read: '{input_string}'")

if __name__ == "__main__":
    main()