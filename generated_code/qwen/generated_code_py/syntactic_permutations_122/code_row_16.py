import ctypes

# Allocate two chunks of memory, each of size 10 bytes
chunk1 = ctypes.create_string_buffer(10)
chunk2 = ctypes.create_string_buffer(10)

# Populate chunk1 with some data (for demonstration purposes)
ctypes.memset(chunk1, ord('A'), 10)  # Fill the buffer with 'A'

# Copy contents of chunk1 into chunk2
ctypes.memmove(chunk2, chunk1, 10)

# Free the first chunk (in C, you would use free(), but in Python, memory management is automatic)
del chunk1

# Free the second chunk
del chunk2