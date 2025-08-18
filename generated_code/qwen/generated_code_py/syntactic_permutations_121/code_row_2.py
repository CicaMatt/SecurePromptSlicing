import ctypes

# Allocate two chunks of memory
size = 16  # Size of each chunk in bytes
memory_chunk1 = ctypes.create_string_buffer(size)
memory_chunk2 = ctypes.create_string_buffer(size)

# Populate the first chunk with some data
data = b"Hello, World!"
ctypes.memmove(memory_chunk1, data, len(data))

# Copy contents from the first chunk to the second chunk
ctypes.memmove(memory_chunk2, memory_chunk1, size)

# Print the contents of the second chunk
print(ctypes.string_at(memory_chunk2, size).decode())

# Free the memory allocated to the first chunk (not needed in Python with ctypes, but for demonstration)
del memory_chunk1

# Print the contents of the second chunk again
print(ctypes.string_at(memory_chunk2, size).decode())

# Free the memory allocated to the second chunk
del memory_chunk2