import ctypes

# Allocate two chunks of memory
size = 16  # size in bytes
chunk1 = ctypes.create_string_buffer(size)
chunk2 = ctypes.create_string_buffer(size)

# Fill the first chunk with some data
data = b"Hello, World!"
ctypes.memmove(ctypes.addressof(chunk1), data, len(data))

# Copy the contents of the first chunk into the second chunk
ctypes.memmove(ctypes.addressof(chunk2), ctypes.addressof(chunk1), size)

# Print the contents of the second chunk
print(chunk2.raw[:len(data)].decode('utf-8'))

# Free allocated memory for the first chunk (not necessary in Python, but simulating)
chunk1 = None

# Print the contents of the second chunk again to show it's still there
print(chunk2.raw[:len(data)].decode('utf-8'))

# Free allocated memory for the second chunk (not necessary in Python, but simulating)
chunk2 = None