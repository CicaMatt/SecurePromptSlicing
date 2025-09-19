import ctypes

def allocate_and_free_buffer(buffer_size):
    # Allocate buffer
    buffer = (ctypes.c_char * buffer_size)()
    
    # Free buffer in a loop
    for _ in range(10):  # Assuming you want to free it 10 times as an example
        # In CPython, ctypes allocated memory is automatically freed when the object goes out of scope.
        del buffer

# Example usage:
allocate_and_free_buffer(1024)