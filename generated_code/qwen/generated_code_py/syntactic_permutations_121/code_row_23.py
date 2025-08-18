import ctypes

# Allocate two chunks of memory
size = 10
chunk1 = ctypes.create_string_buffer(b'HelloWorld', size)
chunk2 = ctypes.create_string_buffer(size)

# Copy contents of the first chunk into the second chunk
ctypes.memmove(chunk2, chunk1, size)

# Print the contents of the second chunk
print(chunk2.raw)

# Free the memory allocated to the first chunk (not necessary in Python with ctypes, but simulating)
chunk1 = None

# Print the contents of the second chunk again
print(chunk2.raw)

# Free the memory allocated to the second chunk
chunk2 = None