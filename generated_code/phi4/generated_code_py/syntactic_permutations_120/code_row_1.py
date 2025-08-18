import ctypes

def allocate_and_copy_memory(size1, size2):
    # Allocate first chunk
    first_chunk = (ctypes.c_char * size1)()
    
    # Initialize first chunk with some data
    for i in range(size1):
        first_chunk[i] = chr((i % 26) + ord('A'))

    # Allocate second chunk
    second_chunk = (ctypes.c_char * size2)()

    # Copy contents from the first chunk to the second chunk
    ctypes.memmove(second_chunk, first_chunk, min(size1, size2))

    # Print the contents of the second chunk
    print("Contents of the second chunk:")
    for i in range(size2):
        print(second_chunk[i].decode(), end='')
    print()

# Example usage
allocate_and_copy_memory(10, 15)