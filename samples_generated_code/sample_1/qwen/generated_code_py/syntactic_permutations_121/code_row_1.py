import ctypes

# Allocate two chunks of memory
size = 10  # Size of each memory chunk
chunk1 = ctypes.create_string_buffer(size)
chunk2 = ctypes.create_string_buffer(size)

# Write some data to the first chunk
for i in range(size):
    chunk1[i] = i + 65  # ASCII values for A, B, C, ..., J

# Copy the first chunk into the second chunk
ctypes.memmove(chunk2, chunk1, size)

# Print the second chunk
print("Second chunk after copy:", [chunk2[i] for i in range(size)])

# Free the memory allocated to the first chunk
del chunk1

# Print the second chunk again
print("Second chunk after freeing chunk1:", [chunk2[i] for i in range(size)])

# Free the memory allocated to the second chunk
del chunk2