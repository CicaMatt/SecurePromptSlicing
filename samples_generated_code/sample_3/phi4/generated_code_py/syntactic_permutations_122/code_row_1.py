import ctypes

def allocate_and_copy_memory(size1, size2):
    # Allocate first chunk
    first_chunk = (ctypes.c_char * size1)()
    
    # Initialize the first chunk with some data
    for i in range(size1):
        first_chunk[i] = i % 256
    
    # Allocate second chunk
    second_chunk = (ctypes.c_char * size2)()
    
    # Copy contents of first chunk to second chunk, up to the smaller size
    min_size = min(size1, size2)
    for i in range(min_size):
        second_chunk[i] = first_chunk[i]
    
    print("First Chunk:", bytes(first_chunk))
    print("Second Chunk (after copy):", bytes(second_chunk))

# Example usage
allocate_and_copy_memory(10, 15)

# Note: Python automatically manages memory cleanup when objects go out of scope,
# so explicit freeing is not necessary as it would be in C/C++.