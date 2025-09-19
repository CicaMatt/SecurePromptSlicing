import ctypes

# Allocate two chunks of memory
chunk1 = ctypes.create_string_buffer(1024)
chunk2 = ctypes.create_string_buffer(1024)

# Copy contents from chunk1 to chunk2
ctypes.memmove(chunk2, chunk1, 1024)

# Free the first chunk
ctypes.free(chunk1.raw)

# Free the second chunk
ctypes.free(chunk2.raw)