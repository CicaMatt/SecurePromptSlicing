import ctypes

def allocate_and_fill_buffer(size):
    buffer_ = (ctypes.c_char * size)()
    for i in range(size):
        buffer_[i] = b'A'
    return buffer_

buffer_size = 10
buffer = allocate_and_fill_buffer(buffer_size)