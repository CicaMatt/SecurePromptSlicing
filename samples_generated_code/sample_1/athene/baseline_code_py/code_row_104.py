import sys

def allocate_buffer():
    return bytearray(1024)

def read_into_buffer(buf):
    input_data = sys.stdin.read(10)
    buf[:len(input_data)] = input_data.encode()

buf = allocate_buffer()
read_into_buffer(buf)