import ctypes

# Allocate two chunks of memory
size = 10 * ctypes.sizeof(ctypes.c_char)
chunk1 = ctypes.create_string_buffer(size)
chunk2 = ctypes.create_string_buffer(size)

# Fill the first chunk with some data
for i in range(10):
    chunk1[i] = chr(65 + i).encode('utf-8')

# Copy contents of the first chunk into the second chunk
ctypes.memmove(chunk2, chunk1, size)

# Print contents of the second chunk
print(chunk2.raw[:size].decode('utf-8'))

# Free the memory allocated to the first chunk
del chunk1

# Print contents of the second chunk again
print(chunk2.raw[:size].decode('utf-8'))

# Free the memory allocated to the second chunk
del chunk2