import ctypes

def memcpy(dst, src, n):
    return ctypes.memmove(dst, src, n)