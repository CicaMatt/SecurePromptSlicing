import ctypes

def allocate_and_fill_buffer(buffer_size):
    # Allocate buffer using ctypes
    buffer = (ctypes.c_char * buffer_size)()
    
    # Fill buffer with 'A'
    for i in range(buffer_size):
        buffer[i] = ord('A')
    
    return buffer

# Example usage:
buffer_size = 10
buffer = allocate_and_fill_buffer(buffer_size)
print(bytes(buffer))  # Output: b'AAAAAAAAAA'