import ctypes

# Allocate two chunks of memory, each of size 10 bytes
size = 10
chunk1 = ctypes.create_string_buffer(size)
chunk2 = ctypes.create_string_buffer(size)

# Fill the first chunk with some data (e.g., b'abcdefghij')
data = b'abcdefghij'
ctypes.memmove(chunk1, data, size)

# Copy the contents of the first chunk into the second chunk
ctypes.memmove(chunk2, chunk1, size)

# Free the first chunk
ctypes.free(chunk1)

# Free the second chunk
ctypes.free(chunk2)