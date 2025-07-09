import ctypes

def memcpy(destination, source, num):
    ctypes.memmove(destination, source, num)