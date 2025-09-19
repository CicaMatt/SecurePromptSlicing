import ctypes

buffer_size = 1024
buffer = ctypes.create_string_buffer(b'A' * buffer_size)