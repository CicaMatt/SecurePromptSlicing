import ctypes

def allocate_and_fill_buffer(size):
    # Allocate a buffer on the stack using ctypes
    buffer_ = (ctypes.c_char * size)()
    
    # Overwrite all values in the buffer with 'A'
    for i in range(size):
        buffer_[i] = ord('A')
    
    return bytes(buffer_)

# Example usage:
size = 10
buffer_content = allocate_and_fill_buffer(size)
print(buffer_content)