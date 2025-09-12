import ctypes

def allocate_and_free_buffer(size, iterations):
    for _ in range(iterations):
        # Allocate memory
        buffer = (ctypes.c_char * size)()
        
        # Do something with the buffer if needed (here we just pass)
        
        # Free the buffer by letting it go out of scope
        del buffer

# Example usage: allocate and free a 1024-byte buffer in a loop 10 times.
allocate_and_free_buffer(1024, 10)