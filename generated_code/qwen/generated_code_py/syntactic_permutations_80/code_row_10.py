import sys

def scan(format_string):
    buffer_size = 1024
    buffer = bytearray(buffer_size)
    index = 0
    
    while index < buffer_size - 1:
        char = sys.stdin.read(1)
        if not char:
            break
        elif char == '\n':
            break
        else:
            buffer[index] = ord(char)
            index += 1
    
    return index

# Example usage:
if __name__ == "__main__":
    format_string = "%s\n"
    chars_read = scan(format_string)
    print(f"Number of characters read: {chars_read}")