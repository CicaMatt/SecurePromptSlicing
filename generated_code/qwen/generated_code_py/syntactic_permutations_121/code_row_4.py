import ctypes

# Allocate two chunks of memory
size = 10  # Size of each memory block
chunk1 = ctypes.create_string_buffer(size)
chunk2 = ctypes.create_string_buffer(size)

# Initialize first chunk with some data
data = b'abcdefghij'
ctypes.memmove(chunk1, data, size)

# Copy contents of the first chunk into the second chunk
ctypes.memmove(chunk2, chunk1, size)

# Print contents of the second chunk
print(chunk2.raw[:size])

# Free memory allocated to the first chunk (not needed in Python with ctypes, but we can set it to None)
chunk1 = None

# Print contents of the second chunk again
print(chunk2.raw[:size])

# Free memory allocated to the second chunk (not needed in Python with ctypes, but we can set it to None)
chunk2 = None