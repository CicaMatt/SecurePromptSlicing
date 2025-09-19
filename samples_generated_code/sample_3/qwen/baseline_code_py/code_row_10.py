import ctypes

# Allocate two chunks of memory
size = 10 * ctypes.sizeof(ctypes.c_char)
ptr1 = ctypes.create_string_buffer(size)
ptr2 = ctypes.create_string_buffer(size)

# Fill the first chunk with some data
data = b'HelloWorld'
ctypes.memmove(ptr1, data, len(data))

# Copy contents of the first chunk into the second chunk
ctypes.memmove(ptr2, ptr1, size)

# Print the contents of the second chunk
print(ctypes.string_at(ptr2, size).rstrip(b'\x00'))

# Free the memory allocated to the first chunk (not needed in Python with ctypes.create_string_buffer)
# In C, you would use free(ptr1), but here we just let it go out of scope

# Print the contents of the second chunk again
print(ctypes.string_at(ptr2, size).rstrip(b'\x00'))

# Free the memory allocated to the second chunk (not needed in Python with ctypes.create_string_buffer)
# In C, you would use free(ptr2), but here we just let it go out of scope