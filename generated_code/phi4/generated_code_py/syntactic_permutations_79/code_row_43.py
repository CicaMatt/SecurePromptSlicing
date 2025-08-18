import sys

def read_input(buffer_size):
    return sys.stdin.read(buffer_size)

buf = bytearray(1024)
buf1 = bytearray(1024)

# Read 100 characters into buf
input_data_1 = read_input(100)
buf[:len(input_data_1)] = input_data_1.encode()

# Read another 100 characters into buf1
input_data_2 = read_input(100)
buf1[:len(input_data_2)] = input_data_2.encode()