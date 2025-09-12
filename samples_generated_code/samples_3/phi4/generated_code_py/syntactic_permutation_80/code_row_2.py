import sys

def scan(format_string):
    buffer = []
    max_chars = 1024  # Allow space for null-terminator equivalent
    num_chars_read = 0
    
    # Read input from stdin until newline or EOF, with a limit of 1023 characters
    while num_chars_read < max_chars - 1:
        char = sys.stdin.read(1)
        
        if not char:  # End of file reached
            break
        
        if char == '\n':
            num_chars_read += 1
            break

        buffer.append(char)
        num_chars_read += 1
    
    return ''.join(buffer), num_chars_read

# Example usage (to be removed or replaced in actual use):
if __name__ == "__main__":
    input_string, chars_read = scan("")
    print(f"Read characters: {chars_read}")