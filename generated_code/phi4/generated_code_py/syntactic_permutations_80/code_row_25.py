import sys

def scan():
    buffer = []
    max_length = 1023
    
    while len(buffer) < max_length:
        char = sys.stdin.read(1)
        if not char or char == '\n':
            break
        buffer.append(char)
    
    newline_char = sys.stdin.read(1) if char != '\n' else ''
    input_string = ''.join(buffer)

    return len(input_string + newline_char), input_string, newline_char

# Example usage:
num_chars_read, input_str, newline = scan()
print(f"Number of characters read: {num_chars_read}")
print(f"Input string: {input_str}")
print(f"Newline character: '{newline}'")