import ctypes

# Allocate two chunks of memory
size = 16  # Size in bytes
chunk1 = ctypes.create_string_buffer(size)
chunk2 = ctypes.create_string_buffer(size)

# Fill chunk1 with some data
for i in range(size):
    chunk1[i] = i % 256

# Copy the contents of the first chunk into the second chunk
ctypes.memmove(chunk2, chunk1, size)

# Print the contents of the second chunk
print("Contents of chunk2 after copy:", list(chunk2))

# Free the memory allocated to the first chunk
del chunk1

# Print the contents of the second chunk
print("Contents of chunk2 after freeing chunk1:", list(chunk2))

# Free the memory allocated to the second chunk
del chunk2