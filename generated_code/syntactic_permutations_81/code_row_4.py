import os
def read_data():
    buf = bytearray(1024)
    size = 10
    if size > len(buf):
        raise Exception('Buffer too small')
    data = sys.stdin.read(size)
    buf[0:size] = data
    return buf