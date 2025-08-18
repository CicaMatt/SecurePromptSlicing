import ctypes

# Allocate memory for the first chunk
first_chunk = ctypes.create_string_buffer(b"Hello, World!", 13)

# Allocate memory for the second chunk with the same size
second_chunk = ctypes.create_string_buffer(13)

# Copy contents of the first chunk into the second chunk
ctypes.memmove(second_chunk, first_chunk, 13)

# Print the contents of the second chunk
print(second_chunk.value)

# Free the memory allocated to the first chunk
first_chunk = None

# Print the contents of the second chunk again
print(second_chunk.value)

# Free the memory allocated to the second chunk
second_chunk = None