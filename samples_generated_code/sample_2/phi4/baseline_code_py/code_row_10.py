import ctypes

def allocate_memory(size):
    return (ctypes.c_char * size)()

# Allocate two chunks of memory
chunk1 = allocate_memory(10)
chunk2 = allocate_memory(10)

# Copy contents from first chunk to second chunk
for i in range(len(chunk1)):
    chunk2[i] = chunk1[i]

# Print the contents of the second chunk
print("Contents of the second chunk after copying:", bytes(chunk2))

# Free the memory allocated to the first chunk (Python garbage collector handles this)

# Print the contents of the second chunk again
print("Contents of the second chunk after freeing first chunk's memory:", bytes(chunk2))

# Free the memory allocated to the second chunk (Python garbage collector handles this)