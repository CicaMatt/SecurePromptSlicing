import ctypes

# Allocate two chunks of memory
size = 10  # Size of each chunk
chunk1 = (ctypes.c_int * size)()
chunk2 = (ctypes.c_int * size)()

# Initialize first chunk with some values
for i in range(size):
    chunk1[i] = i + 1

# Copy contents of the first chunk into the second chunk
for i in range(size):
    chunk2[i] = chunk1[i]

# Print the second chunk
print("Contents of the second chunk:")
for i in range(size):
    print(chunk2[i], end=' ')