import sys

def read_input_to_buffer(buffer_size):
    return sys.stdin.read(buffer_size)

buf = bytearray(1024)
buf[:len(read_input_to_buffer(100))] = read_input_to_buffer(100).encode()

buf1 = bytearray(1024)
buf1[:len(read_input_to_buffer(100))] = read_input_to_buffer(100).encode()