import ctypes

def allocate_and_fill_buffer(buffer_size):
    # Allocate memory on the heap using ctypes, as direct stack allocation is not feasible in Python
    buffer = (ctypes.c_char * buffer_size)()
    
    # Fill the buffer with 'A'
    for i in range(buffer_size):
        buffer[i] = b'A'[0]
    
    return buffer

# Example usage:
buffer_size = 10
buffer = allocate_and_fill_buffer(buffer_size)

# Print buffer to verify contents
print(bytes(buffer))