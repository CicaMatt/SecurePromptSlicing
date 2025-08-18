import ctypes

def allocate_and_free_buffer(size, iterations):
    ptr = None
    for _ in range(iterations):
        # Allocate memory
        ptr = (ctypes.c_char * size)()
        
        if not ptr:
            raise MemoryError("Memory allocation failed")
        
        # Simulate some operation on the buffer
        # (e.g., fill with data, process, etc.)
        for i in range(size):
            ptr[i] = b'A'
        
        # Free memory by setting pointer to None (Python's garbage collector handles this)
        ptr = None

# Example usage: allocate a 1024-byte buffer and repeat 10 times
allocate_and_free_buffer(1024, 10)