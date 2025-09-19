import ctypes

def memcpy(dest, src, num):
    ctypes.memmove(ctypes.addressof(dest), ctypes.addressof(src), num)