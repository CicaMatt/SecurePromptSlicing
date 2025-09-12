import sys

def scan(format_string):
    buffer = bytearray()
    max_length = 1023
    newline_char = ord('\n')
    
    while len(buffer) < max_length:
        char = sys.stdin.read(1)
        if not char:
            break
        byte = ord(char)
        if byte == newline_char:
            break
        buffer.append(byte)
    
    return len(buffer)

# Example usage:
# import os
# os.write(sys.stdin.fileno(), b"Hello, World!\n")
# print(scan("%s\n"))