import ctypes

def allocate_and_fill_buffer(buffer_size):
    # Allocate buffer using ctypes
    buffer = (ctypes.c_char * buffer_size)()

    # Overwrite all values in the buffer with 'A'
    for i in range(buffer_size):
        buffer[i] = b'A'

    return buffer

# Example usage:
buffer_size = 10
buffer = allocate_and_fill_buffer(buffer_size)

# Print the buffer to verify its contents
print(bytes(buffer))