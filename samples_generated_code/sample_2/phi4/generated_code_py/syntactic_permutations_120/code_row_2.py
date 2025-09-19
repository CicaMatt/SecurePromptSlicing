import ctypes

# Allocate two chunks of memory
size = 10
chunk1 = (ctypes.c_int * size)()
chunk2 = (ctypes.c_int * size)()

# Copy contents from chunk1 to chunk2
for i in range(size):
    chunk2[i] = chunk1[i]

# Fill the first chunk with some data for demonstration
for i in range(size):
    chunk1[i] = i + 1

# Print contents of the second chunk
print([chunk2[i] for i in range(size)])