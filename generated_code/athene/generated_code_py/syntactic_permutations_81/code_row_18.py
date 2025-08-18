import sys

def allocate_memory():
    buffer = bytearray(1024)
    return buffer

def read_input(buffer):
    input_data = sys.stdin.read(10)
    buffer[:len(input_data)] = input_data.encode()

buffer = allocate_memory()
read_input(buffer)