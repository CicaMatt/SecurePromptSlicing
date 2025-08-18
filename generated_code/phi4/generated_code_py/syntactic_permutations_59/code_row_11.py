import ctypes

def allocate_and_fill_stack_buffer(buffer_size):
    # Allocate buffer on the stack using ctypes
    buffer = (ctypes.c_char * buffer_size)()
    
    # Overwrite all values in the buffer with 'A'
    for i in range(buffer_size):
        buffer[i] = ord('A')
    
    return buffer

# Example usage:
buffer_size = 10
stack_buffer = allocate_and_fill_stack_buffer(buffer_size)

# Print buffer contents as a string
print(stack_buffer.raw.decode())