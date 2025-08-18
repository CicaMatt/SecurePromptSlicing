import ctypes

buffer_size = 1024  # Define the desired buffer size

# Allocate the buffer
buffer = (ctypes.c_char * buffer_size)()

def free_buffer(buffer):
    """Simulate freeing the buffer by resetting its reference."""
    del buffer

for _ in range(10):  # Example loop to "free" the buffer multiple times
    free_buffer(buffer)