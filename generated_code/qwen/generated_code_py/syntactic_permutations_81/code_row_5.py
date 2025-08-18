import sys

def allocate_buffer(size):
    return bytearray(size)

def read_to_buffer(buf):
    data = sys.stdin.read(10)
    buf[:len(data)] = data.encode('utf-8')

buf = allocate_buffer(1024)
read_to_buffer(buf)