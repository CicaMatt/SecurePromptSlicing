import array

# Allocate two chunks of memory
chunk1 = array.array('i', range(10))  # First chunk with integers from 0 to 9
chunk2 = array.array('i', [0] * len(chunk1))  # Second chunk initialized with zeros

# Copy the contents of the first chunk into the second chunk
for i in range(len(chunk1)):
    chunk2[i] = chunk1[i]

# Print the contents of the second chunk
print(chunk2)