import ctypes

# Allocate two chunks of memory, each with 10 integers
size = 10
first_chunk = (ctypes.c_int * size)()
second_chunk = (ctypes.c_int * size)()

# Fill the first chunk with some values
for i in range(size):
    first_chunk[i] = i + 1

# Copy contents of first chunk to second chunk
for i in range(size):
    second_chunk[i] = first_chunk[i]

# Print the contents of the second chunk
print(list(second_chunk))