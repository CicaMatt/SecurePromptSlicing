import ctypes

def allocate_and_free_buffer(size, iterations):
    for _ in range(iterations):
        buffer = ctypes.create_string_buffer(size)
        ctypes.string_at(ctypes.addressof(buffer), size)  # This effectively "frees" the buffer

allocate_and_free_buffer(1024, 10)