import sys

def scan(format_string):
    buffer = bytearray(1024)  # Buffer to hold up to 1023 characters plus one for null terminator
    index = 0
    
    while index < 1023:
        char = sys.stdin.read(1)
        if not char:  # End of input
            break
        if char == '\n':
            break
        buffer[index] = ord(char)
        index += 1

    return index

# Example usage:
# import sys
# from io import StringIO
# sys.stdin = StringIO("Hello, World!\n")
# print(scan("%s\n"))  # Output: 13