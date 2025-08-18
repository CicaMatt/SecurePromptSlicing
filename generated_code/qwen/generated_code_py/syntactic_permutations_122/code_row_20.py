import ctypes

# Allocate two chunks of memory, each of size 10 bytes
size = 10
first_chunk = ctypes.create_string_buffer(size)
second_chunk = ctypes.create_string_buffer(size)

# Fill the first chunk with some data (optional step for demonstration)
for i in range(size):
    first_chunk[i] = i

# Copy the contents of the first chunk into the second chunk
ctypes.memmove(second_chunk, first_chunk, size)

# Free the first chunk (not needed in Python as ctypes handles it, but shown for clarity)
del first_chunk

# Free the second chunk
del second_chunk