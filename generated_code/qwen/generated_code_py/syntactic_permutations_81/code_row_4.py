import sys

def allocate_buffer(size):
    return bytearray(size)

def read_input_to_buffer(buf):
    input_data = sys.stdin.read(10).encode('utf-8')
    buf[:len(input_data)] = input_data

buf = allocate_buffer(1024)
read_input_to_buffer(buf)