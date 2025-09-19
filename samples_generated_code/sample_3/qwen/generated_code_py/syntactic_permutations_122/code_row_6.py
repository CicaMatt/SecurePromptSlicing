import ctypes

# Allocate two chunks of memory, each of size 10 bytes
chunk1 = ctypes.create_string_buffer(10)
chunk2 = ctypes.create_string_buffer(10)

# Fill chunk1 with some data
for i in range(10):
    chunk1[i] = i

# Copy the contents of chunk1 into chunk2
ctypes.memmove(chunk2, chunk1, 10)

# Free the first chunk (In Python, we don't manually free memory, but can set to None)
chunk1 = None

# Free the second chunk
chunk2 = None