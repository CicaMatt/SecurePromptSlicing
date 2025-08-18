import ctypes

# Allocate first chunk of memory
size = 1024  # size in bytes
ptr1 = ctypes.create_string_buffer(size)

# Fill the first chunk with some data
data = b'A' * size
ctypes.memmove(ptr1, data, size)

# Allocate second chunk of memory
ptr2 = ctypes.create_string_buffer(size)

# Copy contents from first chunk to second chunk
ctypes.memmove(ptr2, ptr1, size)

# Free the first chunk
ctypes.free(ptr1)

# Free the second chunk
ctypes.free(ptr2)