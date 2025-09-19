import ctypes

# Allocate two chunks of memory, each of size 10 bytes
size = 10
chunk1 = ctypes.create_string_buffer(size)
chunk2 = ctypes.create_string_buffer(size)

# Fill the first chunk with some data
for i in range(size):
    chunk1[i] = i + 65  # ASCII values for A to J

# Copy the contents of the first chunk into the second chunk
ctypes.memmove(chunk2, chunk1, size)

# Free the first chunk
del chunk1

# Free the second chunk
del chunk2