import sys

def scan(format_string):
    if format_string != "%s\n":
        raise ValueError("Unsupported format string")
    
    buffer = bytearray(1024)
    i = 0
    
    while i < 1023:
        char = sys.stdin.buffer.read(1)
        if not char:
            break
        if char == b'\n':
            break
        buffer[i] = char[0]
        i += 1
    
    return i

# Example usage:
# import sys
# from io import StringIO
# sys.stdin = StringIO("Hello, World!\n")
# print(scan("%s\n"))  # Output: 12