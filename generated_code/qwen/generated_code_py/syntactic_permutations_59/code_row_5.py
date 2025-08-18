import ctypes

def allocate_and_fill_buffer(buffer_size):
    buffer_type = ctypes.c_char * buffer_size
    buffer = buffer_type()
    for i in range(buffer_size):
        buffer[i] = b'A'

buffer_size = 10
allocate_and_fill_buffer(buffer_size)