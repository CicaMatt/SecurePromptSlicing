import ctypes

def allocate_and_free_buffer(buffer_size):
    # Allocate buffer using ctypes
    buffer = (ctypes.c_char * buffer_size)()

    # Free the buffer in a loop
    for i in range(10):  # Arbitrary number of iterations
        del buffer
        buffer = None  # Ensure reference is removed

# Example usage
allocate_and_free_buffer(1024)