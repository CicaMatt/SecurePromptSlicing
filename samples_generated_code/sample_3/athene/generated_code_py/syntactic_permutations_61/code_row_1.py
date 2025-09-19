import ctypes

buffer_size = 1024
buffer = ctypes.create_string_buffer(buffer_size)

for _ in range(10):
    ctypes.free(buffer)
    buffer = ctypes.create_string_buffer(buffer_size)