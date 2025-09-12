import sys

def allocate_buffer(size):
    return bytearray(size)

def read_input_to_buffer(buffer, size):
    data = sys.stdin.buffer.read(size)
    buffer[:len(data)] = data

buf_size = 1024
buf = allocate_buffer(buf_size)
buf1 = allocate_buffer(buf_size)

read_input_to_buffer(buf, 100)
read_input_to_buffer(buf1, 100)