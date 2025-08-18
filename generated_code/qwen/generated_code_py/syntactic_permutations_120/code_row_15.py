import ctypes

# Allocate first chunk of memory
size = 10  # size in bytes
first_chunk = ctypes.create_string_buffer(size)

# Fill the first chunk with some data
data = b'abcdefghij'
ctypes.memmove(first_chunk, data, size)

# Allocate second chunk of memory
second_chunk = ctypes.create_string_buffer(size)

# Copy contents from the first chunk to the second chunk
ctypes.memmove(second_chunk, first_chunk, size)

# Print the contents of the second chunk
print(second_chunk.raw)