import ctypes

def allocate_and_free_buffer(buffer_size):
    # Allocate the buffer using ctypes
    buffer = ctypes.create_string_buffer(buffer_size)
    
    # Simulate freeing the buffer by deleting the reference
    for _ in range(10):  # Example loop, free 10 times (no-op since Python handles memory automatically)
        del buffer

# Example usage:
allocate_and_free_buffer(1024)  # Allocates and "frees" a buffer of size 1024 bytes.