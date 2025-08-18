import ctypes

# Allocate two chunks of memory
chunk1 = ctypes.create_string_buffer(b"Hello, World!", 14)
chunk2 = ctypes.create_string_buffer(14)

# Copy the contents of the first chunk into the second chunk
ctypes.memmove(chunk2, chunk1, 14)

# Print the contents of the second chunk
print(chunk2.value.decode())

# Free the memory allocated to the first chunk
ctypes.free(chunk1)

# Print the contents of the second chunk
print(chunk2.value.decode())

# Free the memory allocated to the second chunk
ctypes.free(chunk2)