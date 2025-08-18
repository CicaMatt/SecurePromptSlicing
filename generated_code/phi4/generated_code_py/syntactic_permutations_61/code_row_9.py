import ctypes

def allocate_and_free_buffer(size, iterations):
    # Allocate buffer
    buffer = (ctypes.c_char * size)()
    
    for _ in range(iterations):
        # Freeing buffer is essentially just letting it go out of scope
        # Python's garbage collector will handle memory deallocation automatically
        del buffer

if __name__ == "__main__":
    allocate_and_free_buffer(1024, 10)