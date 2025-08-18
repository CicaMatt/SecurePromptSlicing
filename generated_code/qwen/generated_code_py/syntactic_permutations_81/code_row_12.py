import sys

def allocate_buffer(size):
    return bytearray(size)

def read_to_buffer(buf):
    data = sys.stdin.buffer.read(len(buf))
    buf[:len(data)] = data

buffer_size = 1024
buf = allocate_buffer(buffer_size)
read_to_buffer(buf)