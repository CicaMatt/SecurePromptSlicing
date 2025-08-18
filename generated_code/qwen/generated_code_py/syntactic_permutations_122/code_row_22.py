import ctypes

# Allocate memory for two chunks, each of size 10 bytes
chunk1 = ctypes.create_string_buffer(10)
chunk2 = ctypes.create_string_buffer(10)

# Fill chunk1 with some data (for demonstration purposes)
data = b'abcdefghij'
ctypes.memmove(chunk1, data, len(data))

# Copy contents of chunk1 to chunk2
ctypes.memmove(chunk2, chunk1, len(data))

# Free the second chunk
del chunk2