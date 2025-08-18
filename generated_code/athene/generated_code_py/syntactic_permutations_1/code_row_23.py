import ctypes

def mem_copy(dest, src, count):
    ctypes.memmove(dest, src, count)