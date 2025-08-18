import sys

def allocate_and_copy():
    buf = bytearray(1024)
    buf1 = bytearray(1024)

    try:
        sys.stdin.buffer.readinto(buf[:100])
        sys.stdin.buffer.readinto(buf1[:100])
    except BlockingIOError:
        pass

allocate_and_copy()