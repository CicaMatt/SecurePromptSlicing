import sys

def read_stdin_to_buffer(buffer, size=100):
    data = sys.stdin.read(size)
    buffer[:len(data)] = data.encode('utf-8')

# Allocate the first large buffer
buf_size_1 = 1024
buf = bytearray(buf_size_1)

read_stdin_to_buffer(buf)

# Allocate the second large buffer
buf_size_2 = 1024
buf1 = bytearray(buf_size_2)

read_stdin_to_buffer(buf1)