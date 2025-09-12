import sys
import ctypes

def allocate_and_read(size):
    buf = ctypes.create_string_buffer(size)
    read_size = sys.stdin.buffer.readinto(buf)
    return buf, read_size

size = 1024
buf, _ = allocate_and_read(size)
buf1, _ = allocate_and_read(size)

sys.stdin.buffer.read(100)  # To ensure we only copy 100 characters into the buffers