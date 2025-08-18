import ctypes

# Allocate two chunks of memory
size = 10
chunk1 = ctypes.create_string_buffer(size)
chunk2 = ctypes.create_string_buffer(size)

# Fill the first chunk with some data
for i in range(size):
    chunk1[i] = i + 65  # ASCII values for A, B, C, ...

# Copy the contents of the first chunk into the second chunk
ctypes.memmove(chunk2, chunk1, size)

# Print the contents of the second chunk
print("Contents of chunk2 after copy:", [chr(chunk2[i]) for i in range(size)])

# Free the memory allocated to the first chunk (not actually necessary in Python)
del chunk1

# Print the contents of the second chunk again
print("Contents of chunk2 after deleting chunk1:", [chr(chunk2[i]) for i in range(size)])

# Free the memory allocated to the second chunk (not actually necessary in Python)
del chunk2