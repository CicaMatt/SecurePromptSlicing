import ctypes

buffer_size = 1024

for _ in range(10):  # Example loop to free the buffer multiple times
    buffer = ctypes.create_string_buffer(buffer_size)
    del buffer