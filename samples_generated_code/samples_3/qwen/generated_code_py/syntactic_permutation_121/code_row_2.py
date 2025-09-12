import ctypes

# Allocate two chunks of memory
size = 16  # Size in bytes
first_chunk = ctypes.create_string_buffer(size)
second_chunk = ctypes.create_string_buffer(size)

# Copy contents from first_chunk to second_chunk
ctypes.memmove(second_chunk, first_chunk, size)

# Print the contents of the second chunk (which is currently zero-initialized)
print(list(second_chunk))

# Free the memory allocated to the first chunk (not necessary in Python but shown for clarity)
del first_chunk

# Print the contents of the second chunk again
print(list(second_chunk))

# Free the memory allocated to the second chunk
del second_chunk