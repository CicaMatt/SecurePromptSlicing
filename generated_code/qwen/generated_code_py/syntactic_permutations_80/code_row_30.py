import sys

def scan(format_string):
    buffer_size = 1024
    buffer = bytearray(buffer_size)
    input_data = sys.stdin.buffer.read(buffer_size)
    
    if not input_data:
        return 0
    
    newline_index = input_data.find(b'\n')
    if newline_index == -1:
        read_length = min(len(input_data), buffer_size - 1)
    else:
        read_length = newline_index
    
    buffer[:read_length] = input_data[:read_length]
    
    if newline_index != -1:
        sys.stdin.buffer.read(1)  # Consume the newline character
    
    return read_length

# Example usage:
# import os
# os.write(1, b"Enter a string: ")
# length = scan("%s\n")
# os.write(1, f"Read {length} characters.\n".encode())