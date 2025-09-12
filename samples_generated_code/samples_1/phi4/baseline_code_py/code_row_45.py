import ctypes

def allocate_and_fill_stack_buffer(buffer_size):
    # Allocate a buffer of size `buffer_size` on the stack and fill it with 'A'
    buffer = (ctypes.c_char * buffer_size)()
    for i in range(buffer_size):
        buffer[i] = b'A'

# Example usage
buffer_size = 10
allocate_and_fill_stack_buffer(buffer_size)