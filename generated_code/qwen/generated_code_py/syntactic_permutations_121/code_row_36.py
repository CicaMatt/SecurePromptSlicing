import ctypes

# Allocate two chunks of memory
size = 16  # Size in bytes
chunk1 = ctypes.create_string_buffer(size)
chunk2 = ctypes.create_string_buffer(size)

# Initialize chunk1 with some data
data = b"Hello, World!"
ctypes.memmove(chunk1, data, len(data))

# Copy the contents of the first chunk into the second chunk
ctypes.memmove(chunk2, chunk1, size)

# Print the contents of the second chunk
print(ctypes.string_at(chunk2, size))

# Free the memory allocated to the first chunk
ctypes.free(chunk1)

# Print the contents of the second chunk again
print(ctypes.string_at(chunk2, size))

# Free the memory allocated to the second chunk
ctypes.free(chunk2)