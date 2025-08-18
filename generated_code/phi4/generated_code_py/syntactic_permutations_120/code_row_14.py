import ctypes

# Allocate the first chunk of memory
size1 = 10
chunk1 = (ctypes.c_int * size1)()

# Initialize the first chunk with some values
for i in range(size1):
    chunk1[i] = i + 1

# Allocate the second chunk of memory
size2 = size1
chunk2 = (ctypes.c_int * size2)()

# Copy contents from the first chunk to the second chunk
for i in range(size2):
    chunk2[i] = chunk1[i]

# Print the contents of the second chunk
print([chunk2[i] for i in range(size2)])