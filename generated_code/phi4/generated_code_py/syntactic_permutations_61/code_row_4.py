import ctypes

def allocate_and_free_buffer(buffer_size):
    # Allocate memory
    buffer = (ctypes.c_char * buffer_size)()

    try:
        # Free the buffer in a loop
        for _ in range(10):  # Example loop count, adjust as needed
            del buffer
            buffer = None

    finally:
        print("Buffer freed.")

# Example usage
buffer_size = 1024
allocate_and_free_buffer(buffer_size)