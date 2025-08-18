import ctypes

buffer_size = 1024

# Allocate buffer
buffer = ctypes.create_string_buffer(buffer_size)

# Free buffer in a loop (Note: In Python, memory management is handled by the garbage collector,
# and there's no direct equivalent of C's free(). This loop is just for demonstration.)
for _ in range(5):
    # Simulate freeing buffer by del and gc.collect
    del buffer
    import gc
    gc.collect()
    # Reallocate buffer
    buffer = ctypes.create_string_buffer(buffer_size)