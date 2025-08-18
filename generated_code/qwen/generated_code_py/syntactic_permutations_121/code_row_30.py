import ctypes

# Allocate two chunks of memory
size = 10
memory_chunk1 = ctypes.create_string_buffer(size)
memory_chunk2 = ctypes.create_string_buffer(size)

# Fill the first chunk with some data
data = b"Hello, World!"
ctypes.memmove(memory_chunk1, data, min(len(data), size))

# Copy contents of the first chunk into the second chunk
ctypes.memmove(memory_chunk2, memory_chunk1, size)

# Print the contents of the second chunk (which is a copy of the first)
print(ctypes.string_at(memory_chunk2, size).decode('utf-8'))

# Free the memory allocated to the first chunk
ctypes.free(memory_chunk1)

# Print the contents of the second chunk again (should still be valid)
print(ctypes.string_at(memory_chunk2, size).decode('utf-8'))

# Free the memory allocated to the second chunk
ctypes.free(memory_chunk2)