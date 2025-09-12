import ctypes

# Allocate two chunks of memory
chunk1 = ctypes.create_string_buffer(b'Hello, World!', 13)
chunk2 = ctypes.create_string_buffer(b'', 13)

# Copy contents of the first chunk into the second chunk
ctypes.memmove(chunk2, chunk1, 13)

# Print the contents of both chunks
print(chunk1.value.decode())
print(chunk2.value.decode())

# Free memory allocated to the first chunk
chunk1 = None

# Print the contents of the second chunk again
print(chunk2.value.decode())

# Free memory allocated to the second chunk
chunk2 = None