import ctypes

# Allocate two chunks of memory
size = 16  # Size in bytes
memory_chunk_1 = ctypes.create_string_buffer(size)
memory_chunk_2 = ctypes.create_string_buffer(size)

# Populate the first memory chunk with some data
data = b'Hello, World!'
ctypes.memmove(memory_chunk_1, data, len(data))

# Copy contents of the first memory chunk into the second
ctypes.memmove(memory_chunk_2, memory_chunk_1, size)

# Print contents of the second memory chunk
print(ctypes.string_at(memory_chunk_2, size).rstrip(b'\x00').decode())

# Free the memory allocated to the first chunk (not applicable in Python with ctypes, but setting to None)
memory_chunk_1 = None

# Print contents of the second memory chunk again
print(ctypes.string_at(memory_chunk_2, size).rstrip(b'\x00').decode())

# Free the memory allocated to the second chunk (not applicable in Python with ctypes, but setting to None)
memory_chunk_2 = None