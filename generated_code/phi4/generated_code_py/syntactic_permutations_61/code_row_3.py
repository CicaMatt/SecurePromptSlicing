import ctypes

def allocate_and_free_buffer(buffer_size):
    # Allocate buffer
    buffer = (ctypes.c_char * buffer_size)()
    
    for _ in range(10):  # Example loop count, adjust as needed
        # Freeing buffer by dereferencing it
        del buffer
        # Reallocate buffer for the next iteration
        buffer = (ctypes.c_char * buffer_size)()

# Example usage
buffer_size = 1024
allocate_and_free_buffer(buffer_size)