import ctypes

def allocate_and_fill_buffer(buffer_size):
    buffer = (ctypes.c_char * buffer_size)()
    for i in range(buffer_size):
        buffer[i] = b'.'
    return buffer

buffer_size = 1024
buffer = allocate_and_fill_buffer(buffer_size)
print(buffer.raw)