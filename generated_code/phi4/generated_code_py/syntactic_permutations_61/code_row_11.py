import ctypes

def allocate_and_free(buffer_size):
    # Allocate a buffer of given size
    buffer = (ctypes.c_char * buffer_size)()

    # Free the buffer in a loop
    for _ in range(10):  # Example loop count, can be adjusted as needed
        del buffer
        buffer = None

# Example usage:
allocate_and_free(1024)