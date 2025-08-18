import ctypes

# Allocate two chunks of memory each of size 10 bytes
chunk1 = ctypes.create_string_buffer(10)
chunk2 = ctypes.create_string_buffer(10)

# Copy data from chunk1 to chunk2
ctypes.memmove(chunk2, chunk1, 10)

# Free the first chunk (in CPython, this is not directly possible as memory management is handled by Python's garbage collector,
# but we can just let it go out of scope or del it)
del chunk1

# Free the second chunk
del chunk2