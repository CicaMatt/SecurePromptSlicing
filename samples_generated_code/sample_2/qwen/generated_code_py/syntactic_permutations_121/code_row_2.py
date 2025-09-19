import ctypes

# Allocate two chunks of memory
size = 16  # size in bytes
chunk1 = ctypes.create_string_buffer(size)
chunk2 = ctypes.create_string_buffer(size)

# Fill the first chunk with some data
data = b"Hello, World!"
ctypes.memmove(chunk1, data, len(data))

# Copy the contents of the first chunk into the second chunk
ctypes.memmove(chunk2, chunk1, size)

# Print the contents of the second chunk
print(chunk2.raw[:len(data)].decode())

# Free the memory allocated to the first chunk (not necessary in Python, but shown for illustration)
del chunk1

# Print the contents of the second chunk again
print(chunk2.raw[:len(data)].decode())