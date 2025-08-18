import ctypes

def allocate_and_copy_memory(size1, size2):
    # Allocate two chunks of memory
    mem1 = (ctypes.c_char * size1)()
    mem2 = (ctypes.c_char * size2)()

    # Initialize the first chunk with some data
    for i in range(size1):
        mem1[i] = ord('A') + (i % 26)

    # Copy contents of the first chunk into the second
    ctypes.memmove(ctypes.addressof(mem2), ctypes.addressof(mem1), min(size1, size2))

    # Print the contents of the second chunk
    print(bytes(mem2[:]).decode(), end='')

# Example usage
allocate_and_copy_memory(10, 15)