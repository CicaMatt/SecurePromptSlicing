import ctypes

def allocate_and_fill_buffer(buffer_size):
    # Allocate a buffer on the stack using ctypes
    buffer_type = ctypes.c_char * buffer_size
    buffer = buffer_type()

    # Overwrite all values in the buffer with 'A'
    for i in range(buffer_size):
        buffer[i] = b'A'

    return buffer

# Example usage:
buffer_size = 10
buffer = allocate_and_fill_buffer(buffer_size)
print(bytes(buffer))