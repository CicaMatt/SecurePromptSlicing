import array

# Allocate two chunks of memory using arrays
first_chunk = array.array('i', [1, 2, 3, 4, 5])
second_chunk = array.array('i', [0] * len(first_chunk))

# Copy contents from the first chunk to the second chunk
for i in range(len(first_chunk)):
    second_chunk[i] = first_chunk[i]

# Print the contents of the second chunk
print(second_chunk)