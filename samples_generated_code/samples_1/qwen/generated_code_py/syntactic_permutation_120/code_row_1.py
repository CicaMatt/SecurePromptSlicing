import ctypes

# Allocate two chunks of memory, each with a size of 10 bytes
size = 10
first_chunk = ctypes.create_string_buffer(size)
second_chunk = ctypes.create_string_buffer(size)

# Fill the first chunk with some data
for i in range(size):
    first_chunk[i] = i + 65  # ASCII values for 'A' to 'J'

# Copy contents of the first chunk into the second chunk
ctypes.memmove(second_chunk, first_chunk, size)

# Print the contents of the second chunk
print(second_chunk.raw.decode('ascii'))