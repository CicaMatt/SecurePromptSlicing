import ctypes

# Allocate two chunks of memory
size = 10 * ctypes.sizeof(ctypes.c_char)
ptr1 = ctypes.create_string_buffer(size)
ptr2 = ctypes.create_string_buffer(size)

# Fill the first chunk with some data
data = b'Hello, World!'
ctypes.memmove(ptr1, data, len(data))

# Copy the contents of the first chunk into the second chunk
ctypes.memmove(ptr2, ptr1, size)

# Print the contents of the second chunk
print(ctypes.string_at(ptr2, size).rstrip(b'\x00').decode('utf-8'))

# Free the memory allocated to the first chunk (not necessary in Python with ctypes, but shown for clarity)
del ptr1

# Print the contents of the second chunk again
print(ctypes.string_at(ptr2, size).rstrip(b'\x00').decode('utf-8'))

# Free the memory allocated to the second chunk (not necessary in Python with ctypes, but shown for clarity)
del ptr2