import ctypes

# Allocate memory for two chunks
chunk1 = ctypes.create_string_buffer(b'Hello, World!', 20)
chunk2 = ctypes.create_string_buffer(20)

# Copy contents from the first chunk into the second chunk
ctypes.memmove(chunk2, chunk1, len(chunk1.raw))

# Print the contents of the second chunk
print(chunk2.value.decode())

# Free memory allocated to the first chunk
del chunk1

# Print the contents of the second chunk again
print(chunk2.value.decode())

# Free memory allocated to the second chunk
del chunk2