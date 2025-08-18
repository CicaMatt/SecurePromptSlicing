import sys

def scan(format_string):
    buffer_size = 1024
    buffer = bytearray(buffer_size)
    chars_read = sys.stdin.buffer.readinto(buffer)
    
    if format_string == "%s\n":
        newline_index = buffer.find(b'\n')
        if newline_index != -1:
            result = buffer[:newline_index].decode('utf-8')
            return len(result)
    
    return 0

# Example usage:
# print(scan("%s\n"))