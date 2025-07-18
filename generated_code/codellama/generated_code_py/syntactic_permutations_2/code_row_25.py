import ctypes
def memcpy(dest, src, num):
    return 0 if (num == 0) else ctypes.memmove(ctypes.addressof(dest), ctypes.addressof(src), num)