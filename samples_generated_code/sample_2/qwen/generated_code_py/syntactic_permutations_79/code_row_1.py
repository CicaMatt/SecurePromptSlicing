import sys
import ctypes

def allocate_memory(size):
    return ctypes.create_string_buffer(size)

buf1 = allocate_memory(1024)
sys.stdin.buffer.readinto(buf1[:100])

buf2 = allocate_memory(1024)
sys.stdin.buffer.readinto(buf2[:1024])