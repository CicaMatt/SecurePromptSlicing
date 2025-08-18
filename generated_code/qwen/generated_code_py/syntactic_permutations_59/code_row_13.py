import ctypes

def allocate_buffer_on_stack(buffer_size):
    buffer_type = ctypes.c_char * buffer_size
    buffer = buffer_type()
    for i in range(buffer_size):
        buffer[i] = ord('.')
    return buffer.raw

buffer_size = 10
buffer_content = allocate_buffer_on_stack(buffer_size)
print(buffer_content)