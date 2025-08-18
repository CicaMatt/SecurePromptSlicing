import ctypes

def memmove(dest, src, count):
    ctypes.memmove(dest, src, count)