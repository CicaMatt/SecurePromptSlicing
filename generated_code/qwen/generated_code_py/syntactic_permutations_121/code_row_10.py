import ctypes

# Allocate two chunks of memory
size = 10
chunk1 = ctypes.create_string_buffer(b'abcdefghij', size)
chunk2 = ctypes.create_string_buffer(size)

# Copy contents of the first chunk into the second chunk
ctypes.memmove(chunk2, chunk1, size)

# Print the contents of the second chunk
print(chunk2.raw)

# Free the memory allocated to the first chunk
del chunk1

# Print the contents of the second chunk
print(chunk2.raw)

# Free the memory allocated to the second chunk
del chunk2