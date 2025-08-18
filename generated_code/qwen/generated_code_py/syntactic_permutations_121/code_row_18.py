import ctypes

# Allocate two chunks of memory
size = 1024  # size in bytes
ptr1 = ctypes.create_string_buffer(size)
ptr2 = ctypes.create_string_buffer(size)

# Copy contents from first chunk to second chunk
ctypes.memmove(ptr2, ptr1, size)

# Print the contents of both chunks (hex representation for simplicity)
print("Contents of first chunk:", ptr1.raw.hex())
print("Contents of second chunk:", ptr2.raw.hex())

# Free memory allocated to the first chunk
del ptr1

# Free memory allocated to the second chunk
del ptr2