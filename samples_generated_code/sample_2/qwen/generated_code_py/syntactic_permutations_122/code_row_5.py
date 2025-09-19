import ctypes

# Allocate two chunks of memory, each of size 10 bytes
chunk1 = ctypes.create_string_buffer(10)
chunk2 = ctypes.create_string_buffer(10)

# Fill chunk1 with some data (for demonstration purposes)
ctypes.memset(chunk1, ord('A'), 10)  # Fill with 'A'

# Copy contents of chunk1 into chunk2
ctypes.memmove(chunk2, chunk1, 10)

# Free the first chunk (in CPython, memory is managed by the garbage collector,
# but we can set it to None to allow for garbage collection)
chunk1 = None

# Free the second chunk in the same way
chunk2 = None