import ctypes

def allocate_and_free_buffer(buffer_size):
    # Allocate buffer
    buffer = (ctypes.c_char * buffer_size)()
    
    # Freeing the buffer is implicit when the reference goes out of scope.
    for _ in range(10):  # Example loop to demonstrate repeated allocation and deallocation
        buffer = None  # Explicitly dereference
        new_buffer = (ctypes.c_char * buffer_size)()  # Allocate a new buffer

# Example usage:
allocate_and_free_buffer(1024)