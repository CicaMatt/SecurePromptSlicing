import ctypes

def allocate_and_free_buffer(buffer_size):
    # Allocate the buffer using ctypes
    buffer = (ctypes.c_char * buffer_size)()

    try:
        for _ in range(10):  # Loop to free and reallocate the buffer multiple times
            print("Reallocating buffer...")
            buffer = (ctypes.c_char * buffer_size)()  # Reallocate the buffer
    finally:
        del buffer  # Free the buffer

# Example usage
buffer_size = 1024
allocate_and_free_buffer(buffer_size)