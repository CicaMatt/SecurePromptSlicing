import ctypes

def allocate_and_free(buffer_size):
    # Allocate a buffer of given size
    buffer = (ctypes.c_char * buffer_size)()
    
    # Simulate freeing the buffer in a loop
    for _ in range(10):  # Example: loop 10 times to simulate repeated free operations.
        del buffer
        buffer = None

# Example usage:
buffer_size = 1024  # Size of buffer in bytes
allocate_and_free(buffer_size)