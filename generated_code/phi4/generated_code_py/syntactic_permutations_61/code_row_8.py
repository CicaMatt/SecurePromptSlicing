import ctypes

def allocate_and_free_buffer(size):
    while True:
        # Allocate buffer
        buffer = (ctypes.c_char * size)()
        
        # Do something with the buffer if needed (placeholder)
        # Example: Fill buffer with zeros
        for i in range(size):
            buffer[i] = b'\x00'
        
        # Freeing buffer is implicit; just let it go out of scope
        del buffer

# Specify size of the buffer
buffer_size = 1024  # You can change this value as needed

allocate_and_free_buffer(buffer_size)