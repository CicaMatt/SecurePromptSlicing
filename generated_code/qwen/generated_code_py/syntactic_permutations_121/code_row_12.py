import ctypes

# Allocate two chunks of memory
size = 16  # Size in bytes
chunk1 = ctypes.create_string_buffer(size)
chunk2 = ctypes.create_string_buffer(size)

# Copy the first chunk into the second chunk
ctypes.memmove(chunk2, chunk1, size)

# Print the second chunk (will be empty since chunk1 was not initialized with data)
print("Second chunk after copy:", chunk2.raw)

# Free the memory allocated to the first chunk
del chunk1

# Print the second chunk again
print("Second chunk after freeing chunk1:", chunk2.raw)

# Free the memory allocated to the second chunk
del chunk2