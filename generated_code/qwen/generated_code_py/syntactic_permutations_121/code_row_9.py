import ctypes

# Allocate two chunks of memory
chunk1 = ctypes.create_string_buffer(b'Hello, World!', 14)
chunk2 = ctypes.create_string_buffer(14)

# Copy the contents of the first chunk into the second chunk
ctypes.memmove(chunk2, chunk1, 14)

# Print the contents of the second chunk
print(chunk2.raw.decode())

# Free the memory allocated to the first chunk
# Note: In Python, memory management is handled by the garbage collector,
# and there's no direct equivalent to free(). We just delete the reference.
del chunk1

# Print the contents of the second chunk
print(chunk2.raw.decode())

# Free the memory allocated to the second chunk
del chunk2