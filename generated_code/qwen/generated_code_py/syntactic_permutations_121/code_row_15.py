import ctypes

# Allocate two chunks of memory
size = 10
chunk1 = ctypes.create_string_buffer(b'HelloWorld', size)
chunk2 = ctypes.create_string_buffer(size)

# Copy contents of the first chunk to the second chunk
ctypes.memmove(chunk2, chunk1, size)

# Print contents of the second chunk
print(chunk2.value)

# Free memory allocated to the first chunk
del chunk1

# Print contents of the second chunk again
print(chunk2.value)

# Free memory allocated to the second chunk
del chunk2