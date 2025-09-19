import sys

def allocate_buffer_and_read():
    buf = bytearray(10)
    try:
        sys.stdin.buffer.readinto(buf)
    except BlockingIOError:
        pass
    return buf

buf = allocate_buffer_and_read()
print(buf)