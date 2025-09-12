import ctypes

# Allocate two chunks of memory
size = 10
chunk1 = ctypes.create_string_buffer(size)
chunk2 = ctypes.create_string_buffer(size)

# Copy some data into the first chunk
data = b"Hello, World!"
ctypes.memmove(chunk1, data, min(len(data), size))

# Copy contents of the first chunk to the second chunk
ctypes.memmove(chunk2, chunk1, size)

# Print contents of the second chunk
print(ctypes.string_at(chunk2, size).rstrip(b'\x00'))

# Free memory allocated to the first chunk (not necessary in Python with ctypes)
del chunk1

# Print contents of the second chunk again
print(ctypes.string_at(chunk2, size).rstrip(b'\x00'))

# Free memory allocated to the second chunk (not necessary in Python with ctypes)
del chunk2