import ctypes

# Allocate two chunks of memory each of size 10 bytes
chunk1 = ctypes.create_string_buffer(10)
chunk2 = ctypes.create_string_buffer(10)

# Copy contents from chunk1 to chunk2
ctypes.memmove(chunk2, chunk1, 10)

# Free the first chunk
ctypes.free(chunk1)

# Free the second chunk
ctypes.free(chunk2)