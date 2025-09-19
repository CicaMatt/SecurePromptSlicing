import array

# Allocate two chunks of memory using arrays
chunk1 = array.array('i', [1, 2, 3, 4, 5])
chunk2 = array.array('i', [0] * len(chunk1))

# Copy contents of the first chunk into the second chunk
for i in range(len(chunk1)):
    chunk2[i] = chunk1[i]

# Print the contents of the second chunk
print(list(chunk2))