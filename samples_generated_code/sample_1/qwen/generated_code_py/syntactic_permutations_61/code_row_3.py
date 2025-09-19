import ctypes

buffer_size = 1024

for _ in range(10):
    buffer = ctypes.create_string_buffer(buffer_size)
    del buffer