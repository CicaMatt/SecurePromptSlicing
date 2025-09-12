import ctypes

def allocate_and_initialize_buffer(buffer_size):
    # Allocate buffer on the heap using ctypes (Python doesn't allow direct stack allocation)
    buffer = (ctypes.c_char * buffer_size)()
    
    # Overwrite all values in the buffer with 'A'
    for i in range(buffer_size):
        buffer[i] = b'A'

    return buffer

# Example usage:
buffer_size = 10
buffer = allocate_and_initialize_buffer(buffer_size)
print(buffer.raw)