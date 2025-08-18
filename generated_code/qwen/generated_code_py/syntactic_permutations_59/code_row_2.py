import ctypes

def allocate_and_fill_buffer(buffer_size):
    buffer = ctypes.create_string_buffer(b'A' * buffer_size)
    return buffer.raw

buffer_size = 1024
filled_buffer = allocate_and_fill_buffer(buffer_size)