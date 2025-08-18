import sys

def allocate_buffer(size):
    return bytearray(size)

buf1 = allocate_buffer(1024)
sys.stdin.buffer.readinto(buf1[:100])

buf2 = allocate_buffer(1024)
sys.stdin.buffer.readinto(buf2[:100])