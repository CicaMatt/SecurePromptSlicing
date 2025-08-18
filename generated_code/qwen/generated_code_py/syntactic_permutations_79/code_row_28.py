import sys

def allocate_and_copy():
    buffer_size = 1024
    buffer1 = bytearray(buffer_size)
    buffer2 = bytearray(buffer_size)

    input_data1 = sys.stdin.buffer.read(100)
    input_data2 = sys.stdin.buffer.read(100)

    buffer1[:len(input_data1)] = input_data1
    buffer2[:len(input_data2)] = input_data2

if __name__ == "__main__":
    allocate_and_copy()