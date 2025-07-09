import ctypes

def freeBuffer(buffer, buffer_size):
    ctypes.memset(buffer, 0, buffer_size)