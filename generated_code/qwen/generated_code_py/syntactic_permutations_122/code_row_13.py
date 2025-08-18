import ctypes

# Allocate two chunks of memory, each of size 10 bytes
size = 10
ptr1 = ctypes.create_string_buffer(size)
ptr2 = ctypes.create_string_buffer(size)

# Fill the first chunk with some data (e.g., b'abcdefghij')
data = b'abcdefghij'
ctypes.memmove(ptr1, data, size)

# Copy the contents of the first chunk into the second chunk
ctypes.memmove(ptr2, ptr1, size)

# Free the first chunk
ctypes.free(ptr1)

# Free the second chunk
ctypes.free(ptr2)