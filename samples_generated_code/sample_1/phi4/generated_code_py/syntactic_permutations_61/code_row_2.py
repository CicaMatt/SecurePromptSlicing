import ctypes

def allocate_and_free(buffer_size):
    # Allocate a buffer of given size
    buffer = (ctypes.c_char * buffer_size)()

    # Simulate freeing the buffer multiple times in a loop
    for _ in range(10):  # Adjust the number of iterations as needed
        del buffer
        # In Python, garbage collection will handle memory management.
        # This is to mimic manual free operations.

# Example usage:
buffer_size = 1024  # Set desired buffer size
allocate_and_free(buffer_size)