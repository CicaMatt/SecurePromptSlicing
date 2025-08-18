import ctypes

# Allocate two chunks of memory of size 10
size = 10
chunk1 = ctypes.create_string_buffer(size)
chunk2 = ctypes.create_string_buffer(size)

# Fill chunk1 with some data
for i in range(size):
    chunk1[i] = i

# Copy the contents of the first chunk into the second chunk
ctypes.memmove(chunk2, chunk1, size)

# Free the first chunk
ctypes.free(chunk1)

# Free the second chunk
ctypes.free(chunk2)