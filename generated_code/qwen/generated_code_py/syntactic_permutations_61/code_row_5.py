import ctypes

buffer_size = 1024  # Example buffer size

for _ in range(5):  # Example number of allocations and deallocations
    buffer = ctypes.create_string_buffer(buffer_size)
    del buffer