import ctypes

def allocate_and_fill_buffer(buffer_size):
    buffer = (ctypes.c_char * buffer_size)()
    for i in range(buffer_size):
        buffer[i] = b'A'
    return buffer

buffer_size = 10
allocated_buffer = allocate_and_fill_buffer(buffer_size)
print(list(allocated_buffer))