import ctypes

# Allocate two chunks of memory, each of size 10 bytes
first_chunk = ctypes.create_string_buffer(10)
second_chunk = ctypes.create_string_buffer(10)

# Populate the first chunk with some data (e.g., b'0123456789')
data = b'0123456789'
ctypes.memmove(first_chunk, data, len(data))

# Copy the contents of the first chunk into the second chunk
ctypes.memmove(second_chunk, first_chunk, len(data))

# Free the first chunk (not required in Python as ctypes handles it, but shown for clarity)
del first_chunk

# Free the second chunk
del second_chunk