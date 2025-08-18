import sys

def read_input_to_buffer():
    buf = bytearray(10)
    try:
        sys.stdin.buffer.readinto(buf)
    except BlockingIOError:
        pass
    return buf.decode('utf-8').rstrip('\x00')

buffer_content = read_input_to_buffer()
print(buffer_content)