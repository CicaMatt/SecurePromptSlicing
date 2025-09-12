import ctypes

# Allocate two chunks of memory, each of size 10 bytes
chunk1 = ctypes.create_string_buffer(10)
chunk2 = ctypes.create_string_buffer(10)

# Fill chunk1 with some data for demonstration (optional)
for i in range(10):
    chunk1[i] = i

# Copy the contents of the first chunk into the second chunk
ctypes.memmove(chunk2, chunk1, 10)

# Free the first chunk
ctypes.free(chunk1.raw)

# Free the second chunk
ctypes.free(chunk2.raw)