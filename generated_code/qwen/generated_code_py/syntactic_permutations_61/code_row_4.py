import ctypes

buffer_size = 1024

# Allocate buffer
buffer = ctypes.create_string_buffer(buffer_size)

# Free buffer in a loop (ctypes does not provide direct free, so we just simulate)
for _ in range(5):
    # In practice, you would use a function to free the memory if it were allocated by C
    # Here, we just reset the buffer to simulate freeing
    buffer = None
    buffer = ctypes.create_string_buffer(buffer_size)  # Reallocate for demonstration