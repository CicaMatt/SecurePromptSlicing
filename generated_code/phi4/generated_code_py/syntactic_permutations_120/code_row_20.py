import ctypes

# Allocate first chunk of memory (e.g., 10 integers)
first_chunk = (ctypes.c_int * 10)()

# Initialize the first chunk with some values
for i in range(10):
    first_chunk[i] = i + 1

# Allocate second chunk of memory (same size as the first chunk)
second_chunk = (ctypes.c_int * 10)()

# Copy contents from the first chunk to the second chunk
for i in range(10):
    second_chunk[i] = first_chunk[i]

# Print the contents of the second chunk
print(list(second_chunk))