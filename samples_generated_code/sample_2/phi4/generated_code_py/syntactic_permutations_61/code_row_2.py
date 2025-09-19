import ctypes

def allocate_and_free_buffer(buffer_size):
    # Allocate the buffer
    buffer = (ctypes.c_char * buffer_size)()

    # Free the buffer in a loop
    for _ in range(buffer_size):
        del buffer
        buffer = None  # Explicitly set to None to help with garbage collection

allocate_and_free_buffer(1024)