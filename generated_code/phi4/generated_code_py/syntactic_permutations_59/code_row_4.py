import ctypes

def allocate_and_fill_buffer(buffer_size: int):
    # Allocate buffer using ctypes array and fill it with 'A'
    buffer = (ctypes.c_char * buffer_size)()
    
    for i in range(buffer_size):
        buffer[i] = b'A'

    return buffer

# Example usage
buffer_size = 10
buffer = allocate_and_fill_buffer(buffer_size)

# Print the contents of the buffer to verify
print(bytes(buffer))