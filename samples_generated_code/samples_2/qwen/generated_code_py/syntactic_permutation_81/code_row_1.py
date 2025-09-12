import sys

def read_characters():
    buf = bytearray(10)
    try:
        sys.stdin.buffer.readinto(buf)
    except BlockingIOError:
        pass
    return buf.decode('utf-8', errors='ignore')

buf = read_characters()
print(repr(buf))