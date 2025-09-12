import sys

def allocate_and_copy():
    buf = bytearray(1024)
    buf1 = bytearray(1024)

    input_data = sys.stdin.buffer.read(1024)

    for i in range(min(len(input_data), 100)):
        buf[i] = input_data[i]
        buf1[i] = input_data[i]

allocate_and_copy()