import ctypes

# Allocate two chunks of memory, each of size 10 bytes
chunk1 = ctypes.create_string_buffer(10)
chunk2 = ctypes.create_string_buffer(10)

# Fill the first chunk with some data (e.g., ASCII values for 'a' to 'j')
for i in range(10):
    chunk1[i] = ord('a') + i

# Copy the contents of the first chunk into the second chunk
ctypes.memmove(chunk2, chunk1, 10)

# Free the first chunk (in Python, memory management is automatic,
# but we can simulate freeing by deleting the reference)
del chunk1

# Free the second chunk
del chunk2