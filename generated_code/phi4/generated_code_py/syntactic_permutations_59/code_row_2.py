import ctypes

def allocate_and_fill_buffer(buffer_size):
    # Allocate buffer on the stack using ctypes
    buffer = (ctypes.c_char * buffer_size)()
    
    # Overwrite all values in the buffer with 'A'
    for i in range(buffer_size):
        buffer[i] = b'A'
    
    return buffer

# Example usage
buffer_size = 10
buffer = allocate_and_fill_buffer(buffer_size)
print(bytes(buffer))  # Output: b'AAAAAAAAAA'