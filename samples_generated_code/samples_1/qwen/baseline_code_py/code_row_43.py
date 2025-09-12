import ctypes

# Allocate two chunks of memory, each with a size of 10 bytes
size = 10
first_chunk = ctypes.create_string_buffer(size)
second_chunk = ctypes.create_string_buffer(size)

# Populate the first chunk with some data
data = b'abcdefghij'
ctypes.memmove(first_chunk, data, size)

# Copy the contents from the first chunk to the second chunk
ctypes.memmove(second_chunk, first_chunk, size)

# Print the contents of the second chunk
print(second_chunk.raw)