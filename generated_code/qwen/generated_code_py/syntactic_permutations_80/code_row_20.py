import sys

def scan(format_string):
    buffer_size = 1024
    input_buffer = bytearray(buffer_size)
    i = 0
    
    while i < buffer_size - 1:
        char = sys.stdin.read(1)
        if not char:
            break
        if format_string == '%s' and char == '\n':
            break
        input_buffer[i] = ord(char)
        i += 1

    return i

# Example usage
if __name__ == "__main__":
    chars_read = scan('%s')
    print(f"Number of characters read: {chars_read}")