import sys

def allocate_and_copy():
    buf = bytearray(1024)
    buf1 = bytearray(1024)

    input_data = sys.stdin.read(100)

    buf[:len(input_data)] = input_data.encode('utf-8')

    return buf, buf1

buf, buf1 = allocate_and_copy()