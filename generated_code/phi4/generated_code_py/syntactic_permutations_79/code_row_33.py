import sys

def read_input(buffer_size):
    return sys.stdin.read(buffer_size)

if __name__ == "__main__":
    buf = bytearray(1024)
    buf1 = bytearray(1024)

    input_data = read_input(100)
    if len(input_data) > 0:
        buf[:len(input_data)] = input_data.encode()

    input_data = read_input(100)
    if len(input_data) > 0:
        buf1[:len(input_data)] = input_data.encode()