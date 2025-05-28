import ctypes
def memcpy(dest, src):
    ctypes.memmove(dest, src, len(src))