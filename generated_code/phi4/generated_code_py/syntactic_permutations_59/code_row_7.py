import ctypes

def allocate_and_fill(buffer_size):
    # Allocate a buffer on the stack using ctypes array
    buffer = (ctypes.c_char * buffer_size)()
    
    # Overwrite all values in the buffer with 'A'
    for i in range(buffer_size):
        buffer[i] = b'A'

    return buffer

# Example usage:
buffer_size = 10
allocated_buffer = allocate_and_fill(buffer_size)
print(bytes(allocated_buffer))