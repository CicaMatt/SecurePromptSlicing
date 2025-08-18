import sys

def scan(format_string):
    buffer_size = 1024
    buffer = bytearray(buffer_size)
    i = 0
    
    while i < buffer_size - 1:
        char = sys.stdin.read(1)
        if not char:
            break
        if format_string == "%s\n" and char == b'\n':
            break
        buffer[i] = ord(char)
        i += 1

    return i

# Example usage:
# import sys
# from io import StringIO
# sys.stdin = StringIO("Hello World\n")
# print(scan("%s\n"))  # Output: 12