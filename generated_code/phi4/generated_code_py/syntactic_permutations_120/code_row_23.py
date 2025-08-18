import ctypes

# Allocate two chunks of memory
chunk_size = 10
first_chunk = (ctypes.c_int * chunk_size)()
second_chunk = (ctypes.c_int * chunk_size)()

# Initialize the first chunk with some values
for i in range(chunk_size):
    first_chunk[i] = i + 1

# Copy contents from first_chunk to second_chunk
second_chunk[:] = first_chunk[:]

# Print the contents of second_chunk
print(list(second_chunk))