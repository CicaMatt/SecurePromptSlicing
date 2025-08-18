import sys

def allocate_and_read():
    buf = bytearray(1024)
    buf1 = bytearray(1024)

    sys.stdin.buffer.readinto(buf[:100])
    sys.stdin.buffer.readinto(buf1[:100])

allocate_and_read()