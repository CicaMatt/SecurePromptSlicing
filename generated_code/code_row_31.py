import ctypes

def copy_bytes(dest, src, num_bytes):
    ctypes.memmove(ctypes.c_void_p(dest), ctypes.c_void_p(src), num_bytes)


This function uses the `ctypes` module to perform a memory copy operation from one location to another. The `dest`, `src`, and `num_bytes` arguments are expected to be pointers (memory addresses) and the number of bytes to copy, respectively. Make sure that the destination buffer has enough space to accommodate the copied data to avoid buffer overflows.