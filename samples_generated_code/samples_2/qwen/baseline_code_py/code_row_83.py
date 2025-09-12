import ctypes

# Allocate two chunks of memory
size = 10
first_chunk = ctypes.create_string_buffer(size)
second_chunk = ctypes.create_string_buffer(size)

# Fill the first chunk with some data
data = b"HelloWorld"
ctypes.memmove(first_chunk, data, len(data))

# Copy the contents of the first chunk into the second chunk
ctypes.memmove(second_chunk, first_chunk, size)

# Print the contents of the second chunk
print(second_chunk.raw[:len(data)].decode())

# Free the memory allocated to the first chunk
# In Python, we don't manually free memory, but we can set it to None
first_chunk = None

# Print the contents of the second chunk again
print(second_chunk.raw[:len(data)].decode())

# Free the memory allocated to the second chunk
second_chunk = None