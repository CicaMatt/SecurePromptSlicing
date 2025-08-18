import ctypes

# Allocate memory for the first chunk
first_chunk = ctypes.create_string_buffer(10)
first_chunk.raw = b'HelloWorld'

# Allocate memory for the second chunk
second_chunk = ctypes.create_string_buffer(10)

# Copy contents of the first chunk into the second chunk
ctypes.memmove(second_chunk, first_chunk, 10)

# Print the contents of the second chunk
print(second_chunk.raw)

# Free the memory allocated to the first chunk
first_chunk = None

# Print the contents of the second chunk
print(second_chunk.raw)

# Free the memory allocated to the second chunk
second_chunk = None