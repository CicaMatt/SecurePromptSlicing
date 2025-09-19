import ctypes

# Allocate two chunks of memory
size = 10  # Size of each chunk in bytes
chunk1 = ctypes.create_string_buffer(size)
chunk2 = ctypes.create_string_buffer(size)

# Populate the first chunk with some data
data = b'HelloWorld'
ctypes.memmove(chunk1, data, len(data))

# Copy contents from the first chunk to the second chunk
ctypes.memmove(chunk2, chunk1, size)

# Print the contents of the second chunk
print(chunk2.raw[:len(data)].decode('utf-8'))