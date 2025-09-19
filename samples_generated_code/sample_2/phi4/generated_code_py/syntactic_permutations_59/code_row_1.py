import ctypes

def create_and_fill_buffer(buffer_size):
    # Allocate a buffer of bytes with the given size
    buffer = (ctypes.c_char * buffer_size)()

    # Overwrite all values in the buffer with 'A'
    for i in range(buffer_size):
        buffer[i] = b'A'

    return buffer

# Example usage:
buffer_size = 10
buffer = create_and_fill_buffer(buffer_size)

# Convert buffer to a string to display its contents
print(bytes(buffer).decode())