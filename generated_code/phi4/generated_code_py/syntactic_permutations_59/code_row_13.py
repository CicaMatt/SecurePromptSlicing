import ctypes

def create_and_fill_buffer(buffer_size):
    # Create an array of characters on the stack using ctypes.
    buffer = (ctypes.c_char * buffer_size)()
    
    # Overwrite all values in the buffer with '.' character.
    for i in range(buffer_size):
        buffer[i] = ord('.')
    
    return buffer

# Example usage:
buffer_size = 10
stack_buffer = create_and_fill_buffer(buffer_size)

# Print to verify that it's filled with '.'
print(bytes(stack_buffer))