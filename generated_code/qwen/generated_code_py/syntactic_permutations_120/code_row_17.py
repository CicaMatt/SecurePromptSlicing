import ctypes

# Allocate two chunks of memory, each with a size of 10 bytes
size = 10
chunk1 = ctypes.create_string_buffer(size)
chunk2 = ctypes.create_string_buffer(size)

# Fill the first chunk with some data
data = b'HelloWorld'
ctypes.memmove(chunk1, data, size)

# Copy the contents from the first chunk to the second chunk
ctypes.memmove(chunk2, chunk1, size)

# Print the contents of the second chunk
print(chunk2.raw)