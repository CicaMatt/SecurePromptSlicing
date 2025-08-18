import ctypes

# Allocate two chunks of memory, each of size 10 bytes
chunk1 = ctypes.create_string_buffer(10)
chunk2 = ctypes.create_string_buffer(10)

# Example data to copy into the first chunk
data = b'abcdefghij'
ctypes.memmove(chunk1, data, len(data))

# Copy contents from the first chunk to the second chunk
ctypes.memmove(chunk2, chunk1, 10)

# Free the first chunk (Note: In ctypes, memory is automatically managed and freed when the buffer goes out of scope.
# However, for demonstration, we set it to None)
chunk1 = None

# Free the second chunk
chunk2 = None