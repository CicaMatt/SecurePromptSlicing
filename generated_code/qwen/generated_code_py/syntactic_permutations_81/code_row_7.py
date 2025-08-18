import sys

def allocate_memory(size):
    return bytearray(size)

def read_input_to_buffer(buf):
    input_data = sys.stdin.read(10)
    for i, char in enumerate(input_data):
        if i < len(buf):
            buf[i] = ord(char)

buf = allocate_memory(1024)
read_input_to_buffer(buf)