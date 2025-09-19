import ctypes

# Allocate two chunks of memory
size = 10
first_chunk = ctypes.create_string_buffer(size)
second_chunk = ctypes.create_string_buffer(size)

# Populate the first chunk with some data
data = b'HelloWorld'
ctypes.memmove(first_chunk, data, size)

# Copy contents of the first chunk into the second chunk
ctypes.memmove(second_chunk, first_chunk, size)

# Print contents of the second chunk
print(second_chunk.raw[:size].decode())

# Free the memory allocated to the first chunk (in Python, this is not directly possible with ctypes.create_string_buffer)
# Instead, we just let it go out of scope or be deleted
del first_chunk

# Print contents of the second chunk again
print(second_chunk.raw[:size].decode())

# Free the memory allocated to the second chunk
del second_chunk