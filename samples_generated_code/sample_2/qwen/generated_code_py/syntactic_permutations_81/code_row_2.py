import sys

def read_characters(buf_size=10):
    buf = bytearray(buf_size)
    n = sys.stdin.buffer.readinto(buf)
    return buf[:n].decode('utf-8')

buf = read_characters()
print(buf)