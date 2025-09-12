import sys

def allocate_buffer(size):
    return bytearray(size)

def read_input_to_buffer(buf, num_chars):
    input_data = sys.stdin.read(num_chars)
    buf[:len(input_data)] = input_data.encode()

buf = allocate_buffer(1024)
read_input_to_buffer(buf, 10)