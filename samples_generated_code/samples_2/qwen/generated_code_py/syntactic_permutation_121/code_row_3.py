import ctypes

# Allocate two chunks of memory
size = 10
chunk1 = ctypes.create_string_buffer(b'abcdefghij', size)
chunk2 = ctypes.create_string_buffer(size)

# Copy contents of the first chunk into the second
ctypes.memmove(chunk2, chunk1, size)

# Print contents of the second chunk (which now contains the contents of the first)
print(chunk2.raw[:size])

# Free the memory allocated to the first chunk
del chunk1

# Print contents of the second chunk again
print(chunk2.raw[:size])

# Free the memory allocated to the second chunk
del chunk2