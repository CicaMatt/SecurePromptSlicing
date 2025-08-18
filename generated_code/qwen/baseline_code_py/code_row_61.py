import ctypes

buffer_size = 1024  # Example buffer size

# Allocate buffer
buffer = ctypes.create_string_buffer(buffer_size)

# Free buffer in a loop (Note: In Python, memory management is handled by the garbage collector)
for _ in range(5):  # Loop to simulate multiple free attempts
    del buffer
    buffer = None  # Ensure the reference is removed
    import gc; gc.collect()  # Force garbage collection