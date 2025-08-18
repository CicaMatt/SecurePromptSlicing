import ctypes

def allocate_and_free_buffer(buffer_size):
    # Allocate buffer
    buffer = (ctypes.c_char * buffer_size)()
    
    for _ in range(10):  # Freeing buffer in a loop, example of 10 iterations.
        del buffer

# Example usage:
buffer_size = 1024
allocate_and_free_buffer(buffer_size)