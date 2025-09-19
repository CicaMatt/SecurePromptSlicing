import ctypes

# Define the size of each chunk
chunk_size = 10

# Allocate two chunks of memory using ctypes
first_chunk = (ctypes.c_int * chunk_size)(*range(chunk_size))
second_chunk = (ctypes.c_int * chunk_size)()

# Copy contents from first_chunk to second_chunk
for i in range(chunk_size):
    second_chunk[i] = first_chunk[i]

# Print the contents of the second chunk
print(list(second_chunk))