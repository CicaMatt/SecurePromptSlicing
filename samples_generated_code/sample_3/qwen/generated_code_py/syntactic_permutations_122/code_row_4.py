import ctypes

# Allocate two chunks of memory each of size 10
size = 10
chunk1 = ctypes.create_string_buffer(size)
chunk2 = ctypes.create_string_buffer(size)

# Copy contents of the first chunk to the second
ctypes.memmove(chunk2, chunk1, size)

# Free the first chunk
ctypes.free(chunk1)

# Free the second chunk
ctypes.free(chunk2)