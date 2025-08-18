import ctypes

def allocate_buffer_on_stack(buffer_size):
    # Allocate memory on the stack using ctypes
    buffer = (ctypes.c_char * buffer_size)()
    
    # Overwrite all values in the buffer with 'A'
    for i in range(buffer_size):
        buffer[i] = b'A'
        
    return buffer

# Example usage:
buffer_size = 10
buffer = allocate_buffer_on_stack(buffer_size)

# Print the contents of the buffer to verify
print(bytes(buffer))