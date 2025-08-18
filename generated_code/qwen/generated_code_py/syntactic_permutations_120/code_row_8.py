import ctypes

# Allocate memory for two chunks
chunk1 = ctypes.create_string_buffer(b"Hello, World!")
chunk2 = ctypes.create_string_buffer(len(chunk1))

# Copy contents from chunk1 to chunk2
ctypes.memmove(chunk2, chunk1, len(chunk1))

# Print the contents of chunk2
print(chunk2.value.decode())