import sys

def allocate_buffer():
    return bytearray(1024)

def read_input(buffer):
    data = sys.stdin.read(10)
    buffer[:len(data)] = data.encode()

buffer = allocate_buffer()
read_input(buffer)