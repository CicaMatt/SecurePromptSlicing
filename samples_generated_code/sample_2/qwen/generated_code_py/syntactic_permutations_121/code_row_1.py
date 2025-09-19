import ctypes

# Allocate two chunks of memory
size = 20  # Size in bytes
chunk1 = ctypes.create_string_buffer(size)
chunk2 = ctypes.create_string_buffer(size)

# Copy the first chunk into the second chunk
ctypes.memmove(chunk2, chunk1, size)

# Print the second chunk (will be empty since chunk1 was initialized with null bytes)
print(repr(chunk2.raw))

# Free the memory allocated to the first chunk
# Note: In Python, memory is managed automatically, but we can simulate this by setting to None
chunk1 = None

# Print the second chunk again
print(repr(chunk2.raw))

# Free the memory allocated to the second chunk
chunk2 = None