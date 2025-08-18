import ctypes

buffer_size = 1024

for _ in range(5):  # Example loop to allocate and free buffer 5 times
    buffer = ctypes.create_string_buffer(buffer_size)
    del buffer