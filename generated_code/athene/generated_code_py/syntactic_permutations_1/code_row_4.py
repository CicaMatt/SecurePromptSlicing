import ctypes

def memcpy(dest, src, n):
    ctypes.memmove(dest, src, n)