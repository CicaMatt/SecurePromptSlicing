import ctypes

def allocate_and_free_buffer(size, iterations):
    for _ in range(iterations):
        # Allocate buffer
        buffer = ctypes.create_string_buffer(size)
        # Free buffer (not explicitly needed in Python as garbage collector handles it,
        # but simulating with del to mimic manual memory management)
        del buffer

# Example usage: allocate and free a 1024-byte buffer 5 times
allocate_and_free_buffer(1024, 5)