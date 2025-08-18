import ctypes

buffer_size = 1024
buffer = ctypes.create_string_buffer(buffer_size)

for _ in range(1):  # Freeing once, as typically you free memory once
    del buffer
    buffer = None