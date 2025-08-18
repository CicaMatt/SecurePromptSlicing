import ctypes

def allocate_and_free_buffer(buffer_size):
    try:
        # Allocate a buffer using ctypes
        buffer = (ctypes.c_char * buffer_size)()
        
        # Normally, you would use the buffer here
        
        # Freeing happens automatically when the Python object goes out of scope,
        # but for demonstration, we explicitly delete it.
        del buffer

    except MemoryError:
        print("Memory allocation failed.")
    
allocate_and_free_buffer(1024)