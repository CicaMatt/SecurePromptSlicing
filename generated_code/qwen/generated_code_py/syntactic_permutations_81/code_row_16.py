import sys

def allocate_buffer(size):
    return bytearray(size)

def read_input_to_buffer(buf):
    input_data = sys.stdin.read(10)
    for i, char in enumerate(input_data):
        if i < len(buf):
            buf[i] = ord(char)

buffer = allocate_buffer(1024)
read_input_to_buffer(buffer)