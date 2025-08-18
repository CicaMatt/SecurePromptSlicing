import ctypes

# Allocate two chunks of memory
size = 10
first_chunk = ctypes.create_string_buffer(size)
second_chunk = ctypes.create_string_buffer(size)

# Fill the first chunk with some data
ctypes.memset(first_chunk, ord('A'), size)  # Fill with 'A'

# Copy contents from the first chunk to the second chunk
ctypes.memmove(second_chunk, first_chunk, size)

# Print the contents of the second chunk
print(second_chunk.raw.decode())

# Free the memory allocated to the first chunk (not actually necessary in Python)
del first_chunk

# Print the contents of the second chunk again
print(second_chunk.raw.decode())

# Free the memory allocated to the second chunk (not actually necessary in Python)
del second_chunk