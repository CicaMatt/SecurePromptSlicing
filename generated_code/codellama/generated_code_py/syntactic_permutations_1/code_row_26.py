def copy_bytes(destination, source, num):
    import ctypes
    ctypes.memmove(destination, source, num)