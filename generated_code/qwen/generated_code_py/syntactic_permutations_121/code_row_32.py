import ctypes

# Allocate two chunks of memory
size = 10
first_chunk = ctypes.create_string_buffer(size)
second_chunk = ctypes.create_string_buffer(size)

# Initialize first chunk with some data
data = b'abcdefghij'
ctypes.memmove(first_chunk, data, size)

# Copy contents from the first chunk to the second chunk
ctypes.memmove(second_chunk, first_chunk, size)

# Print contents of the second chunk
print(second_chunk.raw[:size])

# Free memory allocated to the first chunk
first_chunk = None

# Print contents of the second chunk again
print(second_chunk.raw[:size])

# Free memory allocated to the second chunk
second_chunk = None