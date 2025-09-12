import ctypes

def allocate_and_clear(size):
    buffer = (ctypes.c_ubyte * size)()
    ctypes.memset(buffer, 0, size)
    return buffer

# Example usage
size = 1024
memory_block = allocate_and_clear(size)