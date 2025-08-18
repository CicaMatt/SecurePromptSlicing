import ctypes

def memcpy(dest, src, num):
    ctypes.memmove(dest, src, num)