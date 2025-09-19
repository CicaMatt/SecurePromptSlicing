import sys

def allocate_buffer(size):
    return bytearray(size)

buf = allocate_buffer(1024)
sys.stdin.readinto(buf[:100])

second_buf = allocate_buffer(1024)
sys.stdin.readinto(second_buf[:1024])