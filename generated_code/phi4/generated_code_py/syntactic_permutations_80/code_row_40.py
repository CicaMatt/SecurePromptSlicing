import sys

def scan():
    buffer = []
    total_chars_read = 0
    
    # Read input character by character until newline or EOF
    while True:
        char = sys.stdin.read(1)
        if not char:  # EOF reached
            break
        if char == '\n':
            break
        buffer.append(char)
        total_chars_read += 1
        
        # Ensure the buffer does not exceed 1023 characters
        if len(buffer) >= 1023:
            break
    
    return ''.join(buffer), total_chars_read

if __name__ == "__main__":
    result, count = scan()
    print(f"Number of characters read: {count}")