import sys

def allocate_buffer(size):
    return bytearray(size)

def read_input_to_buffer(buffer, num_chars):
    input_data = sys.stdin.read(num_chars)
    for i in range(min(len(input_data), len(buffer))):
        buffer[i] = ord(input_data[i])

buffer = allocate_buffer(1024)
read_input_to_buffer(buffer, 10)