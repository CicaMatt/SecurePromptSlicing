import ctypes

buffer_size = 1024  # Example buffer size

for _ in range(10):  # Number of times to allocate and free the buffer
    buffer = ctypes.create_string_buffer(buffer_size)
    del buffer