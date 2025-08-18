import sys

def allocate_buffer(size):
    return bytearray(size)

def read_input_to_buffer(buf):
    input_data = sys.stdin.read(10)
    buf[:len(input_data)] = input_data.encode('utf-8')

buf = allocate_buffer(1024)
read_input_to_buffer(buf)