import ctypes

buffer_size = 1024
loop_count = 5

for _ in range(loop_count):
    buffer = ctypes.create_string_buffer(buffer_size)
    ctypes.free(buffer)