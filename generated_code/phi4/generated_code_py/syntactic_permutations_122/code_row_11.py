import ctypes

def allocate_memory(size):
    return (ctypes.c_int * size)()

def free_memory(memory_chunk):
    del memory_chunk

# Allocate two chunks of memory, each with 10 integers
chunk1 = allocate_memory(10)
chunk2 = allocate_memory(10)

# Initialize the first chunk with some values for demonstration
for i in range(10):
    chunk1[i] = i + 1

# Copy contents from the first chunk to the second chunk
ctypes.memmove(ctypes.addressof(chunk2), ctypes.addressof(chunk1), ctypes.sizeof(chunk1))

# Free the first chunk
free_memory(chunk1)

# Verify copying by printing the second chunk
for value in chunk2:
    print(value, end=' ')
print()

# Free the second chunk
free_memory(chunk2)