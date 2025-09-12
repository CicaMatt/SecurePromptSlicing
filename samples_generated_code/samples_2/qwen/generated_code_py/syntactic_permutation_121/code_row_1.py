import ctypes

# Allocate memory for the first chunk
first_chunk = ctypes.create_string_buffer(b'Hello, World!', 13)

# Allocate memory for the second chunk
second_chunk = ctypes.create_string_buffer(13)

# Copy contents of the first chunk into the second chunk
ctypes.memmove(second_chunk, first_chunk, 13)

# Print the contents of the second chunk
print(second_chunk.raw.decode())

# Free the memory allocated to the first chunk (not necessary in Python, but for demonstration)
del first_chunk

# Print the contents of the second chunk again
print(second_chunk.raw.decode())

# Free the memory allocated to the second chunk (not necessary in Python, but for demonstration)
del second_chunk