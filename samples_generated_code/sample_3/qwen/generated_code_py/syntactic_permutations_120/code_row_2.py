import ctypes

# Allocate two chunks of memory, each with a size of 16 bytes
size = 16
ptr1 = ctypes.create_string_buffer(size)
ptr2 = ctypes.create_string_buffer(size)

# Copy the contents of the first chunk to the second chunk
ctypes.memmove(ptr2, ptr1, size)

# Print the contents of the second chunk
print(bytearray(ptr2))