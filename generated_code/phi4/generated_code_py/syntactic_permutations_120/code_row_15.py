import ctypes

# Allocate first chunk of memory
size1 = 10
first_chunk = (ctypes.c_int * size1)()

# Initialize the first chunk with values
for i in range(size1):
    first_chunk[i] = i + 1

# Allocate second chunk of memory
size2 = 10
second_chunk = (ctypes.c_int * size2)()

# Copy contents from the first chunk to the second chunk
for i in range(min(size1, size2)):
    second_chunk[i] = first_chunk[i]

# Print the contents of the second chunk
print(list(second_chunk))