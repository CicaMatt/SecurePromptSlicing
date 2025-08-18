import array

# Allocate two chunks of memory using arrays
chunk1 = array.array('B', [65, 66, 67, 68, 69])  # Example byte values corresponding to ASCII 'ABCDE'
chunk2 = array.array('B', [0] * len(chunk1))     # Allocate same size with initial zeros

# Copy contents of the first chunk into the second chunk
for i in range(len(chunk1)):
    chunk2[i] = chunk1[i]

# Print the contents of the second chunk
print(chunk2.tolist())