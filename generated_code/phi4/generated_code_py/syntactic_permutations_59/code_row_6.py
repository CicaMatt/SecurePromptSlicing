import ctypes

def allocate_buffer_on_stack(buffer_size):
    # Allocate a block of memory on the stack using ctypes
    buffer = (ctypes.c_char * buffer_size)()
    
    # Overwrite all values in the buffer with 'A'
    for i in range(buffer_size):
        buffer[i] = b'A'

    # Return the buffer to inspect its contents if necessary
    return buffer

# Example usage:
buffer_size = 10
stack_buffer = allocate_buffer_on_stack(buffer_size)

# Print buffer contents as a string
print(stack_buffer.raw.decode('utf-8'))