import ctypes

# Allocate two chunks of memory each of size 10 bytes
chunk1 = ctypes.create_string_buffer(10)
chunk2 = ctypes.create_string_buffer(10)

# Copy the content of the first chunk into the second chunk
ctypes.memmove(chunk2, chunk1, 10)

# Free the first chunk (In Python, memory management is handled by the garbage collector,
# but we can simulate freeing by deleting the reference)
del chunk1

# Free the second chunk
del chunk2