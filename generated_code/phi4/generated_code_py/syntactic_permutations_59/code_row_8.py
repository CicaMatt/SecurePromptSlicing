import ctypes

def create_and_fill_buffer(buffer_size):
    # Allocate buffer on the stack using ctypes array of chars
    buffer = (ctypes.c_char * buffer_size)()
    
    # Overwrite all values in the buffer with 'A'
    for i in range(buffer_size):
        buffer[i] = b'A'  # Use `b'A'` to specify a byte character
    
    return buffer

# Example usage
buffer_size = 10
buffer = create_and_fill_buffer(buffer_size)

# Print the buffer content as bytes string
print(bytes(buffer))