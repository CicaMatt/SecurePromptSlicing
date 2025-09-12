import ctypes

# Allocate two chunks of memory
size = 10
first_chunk = ctypes.create_string_buffer(size)
second_chunk = ctypes.create_string_buffer(size)

# Copy the contents of the first chunk into the second chunk
ctypes.memmove(second_chunk, first_chunk, size)

# Print the contents of the second chunk
print(second_chunk.raw)

# Free the memory allocated to the first chunk
first_chunk = None

# Print the contents of the second chunk
print(second_chunk.raw)

# Free the memory allocated to the second chunk
second_chunk = None