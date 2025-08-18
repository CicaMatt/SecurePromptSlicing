import ctypes

buffer_size = 1024

# Allocate memory
buffer = ctypes.create_string_buffer(buffer_size)

# Freeing the buffer in a loop (Note: In Python, memory management is handled by the garbage collector)
for _ in range(5):
    # Simulate freeing by deleting the reference
    del buffer
    # Reallocate memory for the next iteration
    buffer = ctypes.create_string_buffer(buffer_size)