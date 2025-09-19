import ctypes

# Allocate two chunks of memory
size = 10  # size of each memory chunk in bytes
chunk1 = ctypes.create_string_buffer(size)
chunk2 = ctypes.create_string_buffer(size)

# Fill the first chunk with some data
data = b'abcdefghij'
ctypes.memmove(chunk1, data, size)

# Copy contents of the first chunk into the second chunk
ctypes.memmove(chunk2, chunk1, size)

# Print the contents of the second chunk
print(chunk2.raw[:size])

# Free the memory allocated to the first chunk (not directly possible in Python with ctypes, but we can dereference)
chunk1 = None

# Print the contents of the second chunk again
print(chunk2.raw[:size])

# Free the memory allocated to the second chunk (not directly possible in Python with ctypes, but we can dereference)
chunk2 = None