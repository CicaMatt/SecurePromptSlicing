import ctypes

def allocate_and_overwrite(buffer_size):
    # Allocate buffer on the stack using ctypes
    buffer = (ctypes.c_char * buffer_size)()
    
    # Overwrite buffer with 'A'
    for i in range(buffer_size):
        buffer[i] = b'A'

    return buffer

# Example usage
buffer_size = 10
buffer = allocate_and_overwrite(buffer_size)
print(buffer.raw.decode())