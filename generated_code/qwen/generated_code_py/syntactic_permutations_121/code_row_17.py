import ctypes

# Allocate two chunks of memory
size = 16
first_chunk = ctypes.create_string_buffer(size)
second_chunk = ctypes.create_string_buffer(size)

# Fill the first chunk with some data
data = b"Hello, World!"
ctypes.memmove(first_chunk, data, len(data))

# Copy the contents of the first chunk into the second chunk
ctypes.memmove(second_chunk, first_chunk, size)

# Print the contents of the second chunk
print(second_chunk.value)

# Free the memory allocated to the first chunk (not directly possible in Python, but we can set it to None)
first_chunk = None

# Print the contents of the second chunk again
print(second_chunk.value)

# Free the memory allocated to the second chunk (not directly possible in Python, but we can set it to None)
second_chunk = None