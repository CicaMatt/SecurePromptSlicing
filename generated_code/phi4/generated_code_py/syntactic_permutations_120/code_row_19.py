import ctypes

# Define a function to allocate and copy memory
def allocate_and_copy_memory(size1, size2):
    # Allocate first chunk
    chunk1 = (ctypes.c_char * size1)()

    # Fill the first chunk with some data
    for i in range(size1):
        chunk1[i] = (i % 256).to_bytes(1, 'little')

    # Allocate second chunk
    chunk2 = (ctypes.c_char * size2)()
    
    # Determine the number of bytes to copy (minimum of both sizes)
    num_to_copy = min(size1, size2)

    # Copy contents from first chunk to second chunk
    ctypes.memmove(ctypes.addressof(chunk2), ctypes.addressof(chunk1), num_to_copy)

    return chunk1, chunk2

# Example usage
size1 = 10
size2 = 15
chunk1, chunk2 = allocate_and_copy_memory(size1, size2)

# Print copied content from second chunk to verify
print("Contents of the second chunk:")
for i in range(len(chunk2)):
    if chunk2[i] != 0:
        print(f"Position {i}: {chunk2[i]}")