import ctypes

# Allocate two chunks of memory each of size 10 bytes
size = 10
ptr1 = ctypes.create_string_buffer(size)
ptr2 = ctypes.create_string_buffer(size)

# Initialize the first chunk with some data (e.g., b'0123456789')
data = b'0123456789'
ctypes.memmove(ptr1, data, size)

# Copy the contents of the first chunk into the second chunk
ctypes.memmove(ptr2, ptr1, size)

# Free the first chunk (not actually needed in Python with ctypes, but shown for clarity)
del ptr1

# Free the second chunk
del ptr2