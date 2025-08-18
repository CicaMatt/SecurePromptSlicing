import ctypes

def allocate_memory(size):
    buffer = (ctypes.c_uint8 * size)()
    ctypes.memset(buffer, 0, size)
    return buffer
buffer = allocate_memory(1024)