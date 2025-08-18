import array

# Allocate two chunks of memory
chunk1 = array.array('i', [1, 2, 3, 4, 5])
chunk2 = array.array('i', [0] * len(chunk1))

# Copy the contents of the first chunk into the second chunk
for i in range(len(chunk1)):
    chunk2[i] = chunk1[i]

# Print the contents
print("Chunk 1:", list(chunk1))
print("Chunk 2:", list(chunk2))