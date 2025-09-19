import sys

def allocate_buffer():
    return bytearray(1024)

def read_input(buf):
    input_data = sys.stdin.read(10)
    buf[:len(input_data)] = input_data.encode('utf-8')

buf = allocate_buffer()
read_input(buf)