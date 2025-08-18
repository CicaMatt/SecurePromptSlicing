import ctypes

# Allocate two chunks of memory
size = 16  # Size in bytes
ptr1 = ctypes.create_string_buffer(size)
ptr2 = ctypes.create_string_buffer(size)

# Initialize first chunk with some data
data = b"Hello, World!"
ctypes.memmove(ptr1, data, len(data))

# Copy contents from the first chunk to the second chunk
ctypes.memmove(ptr2, ptr1, size)

# Print the contents of the second chunk
print(ctypes.string_at(ptr2, size).decode())

# Free memory allocated to the first chunk (not needed in ctypes as it's managed)
# but for demonstration, we'll just set the pointer to None
ptr1 = None

# Print the contents of the second chunk again
print(ctypes.string_at(ptr2, size).decode())

# Free memory allocated to the second chunk
ptr2 = None