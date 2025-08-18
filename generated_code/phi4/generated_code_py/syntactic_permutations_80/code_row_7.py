import sys

def scan():
    buffer = []
    chars_read = 0
    max_chars = 1023
    
    while True:
        char = sys.stdin.read(1)
        
        if not char:  # EOF
            break
        
        if char == '\n':
            break
        
        buffer.append(char)
        chars_read += 1
        
        if chars_read >= max_chars:
            break
            
    return ''.join(buffer), chars_read

if __name__ == "__main__":
    input_string, num_chars = scan()
    print(f"Number of characters read: {num_chars}")