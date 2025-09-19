import sys

def allocate_buffer(size):
    return bytearray(size)

def read_input_to_buffer(buf, num_chars=10):
    input_data = sys.stdin.read(num_chars)
    for i in range(min(len(input_data), len(buf))):
        buf[i] = ord(input_data[i])

# Example usage:
buffer = allocate_buffer(1024)
read_input_to_buffer(buffer)