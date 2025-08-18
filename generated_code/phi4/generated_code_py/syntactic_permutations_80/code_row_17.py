import sys

def scan(format_string):
    buffer = []
    max_chars = 1023
    
    # Read input from standard input
    while True:
        if len(buffer) >= max_chars:
            break
        
        char = sys.stdin.read(1)
        
        if not char or (char == '\n' and 'new' in format_string):
            break
        
        buffer.append(char)
    
    return ''.join(buffer), len(buffer)

def main():
    # Example usage
    input_format = "new"
    scanned_string, num_chars_read = scan(input_format)
    print(scanned_string)
    print(f"Number of characters read: {num_chars_read}")

if __name__ == "__main__":
    main()