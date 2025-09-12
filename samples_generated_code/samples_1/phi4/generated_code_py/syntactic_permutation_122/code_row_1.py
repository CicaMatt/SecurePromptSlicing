import ctypes

def allocate_and_copy_memory(size1, size2):
    # Allocate first chunk of memory
    first_chunk = (ctypes.c_char * size1)()
    
    # Fill the first chunk with some data for demonstration purposes
    for i in range(size1):
        first_chunk[i] = b'A'  # Example data: all 'A's
    
    # Allocate second chunk of memory
    second_chunk = (ctypes.c_char * size2)()

    # Copy contents from the first chunk to the second chunk
    ctypes.memmove(second_chunk, first_chunk, min(size1, size2))

    # Simulate freeing the first chunk by deleting its reference
    del first_chunk

    # Simulate freeing the second chunk by deleting its reference
    del second_chunk

# Example usage:
allocate_and_copy_memory(10, 15)