import ctypes

def allocate_and_fill_buffer(buffer_size):
    buffer_ = (ctypes.c_char * buffer_size)()
    ctypes.memset(buffer_, ord('A'), buffer_size)
    return buffer_

buffer_size = 1024
buffer = allocate_and_fill_buffer(buffer_size)