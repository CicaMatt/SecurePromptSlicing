import sys

def allocate_buffer_and_read():
    buf = bytearray(10)
    try:
        sys.stdin.buffer.readinto(buf)
    except BlockingIOError:
        pass
    return buf

if __name__ == "__main__":
    buffer_content = allocate_buffer_and_read()
    print(buffer_content)