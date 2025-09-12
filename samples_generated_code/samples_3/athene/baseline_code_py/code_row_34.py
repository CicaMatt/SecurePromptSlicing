import ctypes

def allocate_buffer(buffer_size):
    buffer = (ctypes.c_char * buffer_size)()
    ctypes.memset(buffer, ord('A'), buffer_size)
    return buffer

buffer_size = 1024
buffer = allocate_buffer(buffer_size)