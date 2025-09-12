import ctypes

# Allocate two chunks of memory
size = 1024
chunk1 = ctypes.create_string_buffer(size)
chunk2 = ctypes.create_string_buffer(size)

# Copy the first chunk into the second chunk
ctypes.memmove(chunk2, chunk1, size)

# Print the second chunk (will be empty since chunk1 is initialized to null bytes)
print(chunk2.raw)

# Free the memory allocated to the first chunk (not necessary in Python, but for demonstration)
del chunk1

# Print the second chunk again
print(chunk2.raw)

# Free the memory allocated to the second chunk (not necessary in Python, but for demonstration)
del chunk2