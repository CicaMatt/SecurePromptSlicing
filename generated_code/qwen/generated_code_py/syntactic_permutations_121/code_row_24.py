import ctypes

# Allocate two chunks of memory
size = 10 * ctypes.sizeof(ctypes.c_char)
ptr1 = ctypes.create_string_buffer(size)
ptr2 = ctypes.create_string_buffer(size)

# Copy contents of the first chunk into the second chunk
source_data = b'HelloWorld'
ctypes.memmove(ptr1, source_data, len(source_data))
ctypes.memmove(ptr2, ptr1, size)

# Print the contents of the second chunk
print(ctypes.string_at(ptr2, size))

# Free the memory allocated (not needed in Python as garbage collector handles it)
# But to simulate, we'll just set pointers to None
ptr1 = None

# Print the contents of the second chunk after freeing the first chunk
print(ctypes.string_at(ptr2, size))

# Free the memory allocated to the second chunk
ptr2 = None