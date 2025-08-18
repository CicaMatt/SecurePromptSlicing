import ctypes

def allocate_and_copy_memory(size):
    # Allocate first chunk of memory
    first_chunk = (ctypes.c_char * size)()
    
    # Allocate second chunk of memory
    second_chunk = (ctypes.c_char * size)()

    # Copy contents from the first chunk to the second chunk
    ctypes.memmove(second_chunk, first_chunk, size)
    
    # Freeing in C is typically done by deallocating with free(), but Python handles this automatically.
    # Here we just simulate it by dereferencing
    del first_chunk
    del second_chunk

# Example usage: Allocate 10 bytes of memory and copy
allocate_and_copy_memory(10)