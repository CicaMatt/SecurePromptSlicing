import ctypes

# Allocate two chunks of memory with a size of 10 integers each
size = 10
first_chunk = (ctypes.c_int * size)()
second_chunk = (ctypes.c_int * size)()

# Initialize first chunk with some values
for i in range(size):
    first_chunk[i] = i + 1

# Copy contents from the first chunk to the second chunk
for i in range(size):
    second_chunk[i] = first_chunk[i]

# Print both chunks to verify copying
print("First Chunk:", list(first_chunk))
print("Second Chunk:", list(second_chunk))