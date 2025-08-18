import ctypes

# Allocate two chunks of memory
chunk1 = ctypes.create_string_buffer(10)
chunk2 = ctypes.create_string_buffer(10)

# Copy contents to the first chunk
ctypes.memmove(chunk1, b"HelloWorld", 10)

# Copy contents from the first chunk to the second chunk
ctypes.memmove(chunk2, chunk1, 10)

# Print the contents of the second chunk
print(ctypes.string_at(chunk2, 10))

# Free the memory allocated to the first chunk
del chunk1

# Print the contents of the second chunk again
print(ctypes.string_at(chunk2, 10))

# Free the memory allocated to the second chunk
del chunk2