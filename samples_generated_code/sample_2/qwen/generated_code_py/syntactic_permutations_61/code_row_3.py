import ctypes

def allocate_and_free_buffer(buffer_size):
    for _ in range(10):  # Example loop to free the buffer multiple times
        buffer = ctypes.create_string_buffer(buffer_size)
        del buffer

buffer_size = 1024  # Size of the buffer in bytes
allocate_and_free_buffer(buffer_size)