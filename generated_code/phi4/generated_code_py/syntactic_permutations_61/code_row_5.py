import ctypes

def allocate_and_free_buffer(buffer_size, iterations):
    # Allocate the buffer
    buffer = (ctypes.c_char * buffer_size)()
    
    try:
        for _ in range(iterations):
            # Simulate freeing by setting to None and reallocating
            buffer = None
            buffer = (ctypes.c_char * buffer_size)()
    finally:
        # Ensure the final allocated buffer is freed
        buffer = None

# Example usage: Allocate a buffer of size 1024 bytes and free it in a loop 100 times.
allocate_and_free_buffer(1024, 100)