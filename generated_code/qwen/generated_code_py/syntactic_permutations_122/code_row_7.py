import ctypes

# Allocate two chunks of memory, each of size 10 bytes
chunk1 = ctypes.create_string_buffer(10)
chunk2 = ctypes.create_string_buffer(10)

# Fill chunk1 with some data for demonstration purposes
for i in range(10):
    chunk1[i] = i + 65  # ASCII values for A-J

# Copy contents of chunk1 into chunk2
ctypes.memmove(chunk2, chunk1, 10)

# Free the first chunk (Note: In Python, memory management is handled automatically,
# but we can simulate freeing by deleting the reference)
del chunk1

# Free the second chunk
del chunk2