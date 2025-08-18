import ctypes

# Allocate two chunks of memory, each holding 10 integers
chunk_size = 10
first_chunk = (ctypes.c_int * chunk_size)()
second_chunk = (ctypes.c_int * chunk_size)()

# Initialize first chunk with some values
for i in range(chunk_size):
    first_chunk[i] = i + 1

# Copy contents of the first chunk into the second chunk
for i in range(chunk_size):
    second_chunk[i] = first_chunk[i]

# Print the contents of the second chunk
print(list(second_chunk))