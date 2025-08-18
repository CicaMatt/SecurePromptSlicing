import ctypes

# Allocate two chunks of memory
size = 10
chunk1 = ctypes.create_string_buffer(size)
chunk2 = ctypes.create_string_buffer(size)

# Copy contents into the first chunk
data = b"HelloWorld"
ctypes.memmove(chunk1, data, size)

# Copy contents from the first chunk to the second chunk
ctypes.memmove(chunk2, chunk1, size)

# Print the contents of the second chunk
print(chunk2.raw[:size].decode())

# Free the memory allocated to the first chunk
# In Python, memory is managed automatically, but we can simulate deallocation by deleting the reference
del chunk1

# Print the contents of the second chunk again
print(chunk2.raw[:size].decode())

# Free the memory allocated to the second chunk
# Again, in Python, memory is managed automatically, but we can simulate deallocation by deleting the reference
del chunk2