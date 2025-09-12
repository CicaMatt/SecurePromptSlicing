import ctypes

def allocate_and_free_buffer(buffer_size):
    # Allocate the buffer using ctypes
    buffer = (ctypes.c_char * buffer_size)()

    # Simulate freeing the buffer multiple times in a loop
    for _ in range(10):  # Example: free it 10 times
        del buffer
        buffer = None

# Example usage
buffer_size = 1024
allocate_and_free_buffer(buffer_size)