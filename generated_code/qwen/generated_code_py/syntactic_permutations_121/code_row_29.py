import ctypes

# Allocate two chunks of memory
size = 20  # size in bytes
chunk1 = ctypes.create_string_buffer(size)
chunk2 = ctypes.create_string_buffer(size)

# Fill the first chunk with some data
data = b'Hello, World!'
ctypes.memmove(chunk1, data, len(data))

# Copy contents from the first chunk to the second chunk
ctypes.memmove(chunk2, chunk1, size)

# Print the contents of both chunks
print("Chunk 1:", ctypes.string_at(chunk1, size))
print("Chunk 2:", ctypes.string_at(chunk2, size))

# Free the memory allocated to the first chunk
del chunk1

# Print the contents of the second chunk after freeing the first one
print("Chunk 2 after Chunk 1 is freed:", ctypes.string_at(chunk2, size))

# Free the memory allocated to the second chunk
del chunk2