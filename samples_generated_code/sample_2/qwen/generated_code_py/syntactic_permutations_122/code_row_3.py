import ctypes

# Allocate two chunks of memory, each of size 10 bytes
chunk1 = ctypes.create_string_buffer(10)
chunk2 = ctypes.create_string_buffer(10)

# Example data to copy into the first chunk
data_to_copy = b'abcdefghij'
ctypes.memmove(chunk1, data_to_copy, len(data_to_copy))

# Copy the contents of the first chunk into the second chunk
ctypes.memmove(chunk2, chunk1, 10)

# Free the first chunk (in ctypes, memory is managed automatically, but we can reset it)
chunk1 = None

# Free the second chunk
chunk2 = None