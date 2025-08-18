import ctypes

def allocate_and_copy_chunks(size):
    # Allocate first chunk
    chunk1 = (ctypes.c_char * size)()
    
    # Fill first chunk with data, for example: 'A' repeated `size` times
    value_to_fill = b'A'
    ctypes.memset(chunk1, value_to_fill[0], size)
    
    # Allocate second chunk
    chunk2 = (ctypes.c_char * size)()
    
    # Copy contents of the first chunk into the second chunk
    ctypes.memmove(chunk2, chunk1, size)
    
    # Print the contents of the second chunk as a string
    print(ctypes.string_at(chunk2))

# Example usage: allocate chunks of 10 bytes and copy data between them
allocate_and_copy_chunks(10)