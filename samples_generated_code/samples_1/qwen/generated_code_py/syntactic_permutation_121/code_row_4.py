import ctypes

# Allocate memory for the first chunk
first_chunk = ctypes.create_string_buffer(b'Hello, World!', 14)

# Allocate memory for the second chunk
second_chunk = ctypes.create_string_buffer(14)

# Copy contents of the first chunk into the second chunk
ctypes.memmove(second_chunk, first_chunk, 14)

# Print the contents of the second chunk
print(second_chunk.raw[:13].decode('utf-8'))

# Free the memory allocated to the first chunk
first_chunk = None

# Print the contents of the second chunk again
print(second_chunk.raw[:13].decode('utf-8'))

# Free the memory allocated to the second chunk
second_chunk = None