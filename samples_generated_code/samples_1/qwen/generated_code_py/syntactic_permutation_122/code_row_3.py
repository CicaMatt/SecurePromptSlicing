import ctypes

# Allocate two chunks of memory each of size 10
size = 10
chunk1 = ctypes.create_string_buffer(size)
chunk2 = ctypes.create_string_buffer(size)

# Fill chunk1 with some data for demonstration
for i in range(size):
    chunk1[i] = i

# Copy the contents of the first chunk into the second
ctypes.memmove(chunk2, chunk1, size)

# Free the first chunk
del chunk1

# Free the second chunk
del chunk2