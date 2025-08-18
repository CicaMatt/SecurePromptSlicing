import sys

def read_input(buffer_size):
    return sys.stdin.read(buffer_size)

buf = bytearray(1024)
buf1 = bytearray(1024)

input_data_1 = read_input(100).encode('utf-8')
input_data_2 = read_input(100).encode('utf-8')

buf[:len(input_data_1)] = input_data_1
buf1[:len(input_data_2)] = input_data_2

print(buf.decode('utf-8', errors='ignore')[:100])
print(buf1.decode('utf-8', errors='ignore')[:100])