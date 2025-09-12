import ctypes

def overwrite_buffer(buffer_size):
    buffer = (ctypes.c_char * buffer_size)()
    for i in range(buffer_size):
        buffer[i] = b'A'

overwrite_buffer(1024)