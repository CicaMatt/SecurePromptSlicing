import ctypes

def allocate_buffer(buffer_size):
    # Allocate a buffer of given size on the heap using ctypes
    buffer = (ctypes.c_char * buffer_size)()
    
    # Overwrite all values in the buffer with 'A'
    for i in range(buffer_size):
        buffer[i] = b'A'
    
    return buffer

# Example usage:
buffer_size = 10
allocated_buffer = allocate_buffer(buffer_size)

# Convert to a Python bytes object and print
print(bytes(allocated_buffer))