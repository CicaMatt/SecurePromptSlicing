import ctypes

# Allocate two chunks of memory, each 1024 bytes
size = 1024
chunk1 = ctypes.create_string_buffer(size)
chunk2 = ctypes.create_string_buffer(size)

# Fill the first chunk with some data (example: b'A' * size)
ctypes.memset(chunk1, ord('A'), size)

# Copy contents of the first chunk into the second chunk
ctypes.memmove(chunk2, chunk1, size)

# Free the first chunk (in ctypes, memory is automatically managed, but we can simulate it)
chunk1 = None

# Free the second chunk
chunk2 = None