import ctypes

# Allocate two chunks of memory, each of size 10 bytes
chunk1 = ctypes.create_string_buffer(10)
chunk2 = ctypes.create_string_buffer(10)

# Fill chunk1 with some data (example: b'0123456789')
ctypes.memset(chunk1, ord('0'), 10)

# Copy the contents of chunk1 into chunk2
ctypes.memmove(chunk2, chunk1, 10)

# Free the first chunk (not directly possible in Python with ctypes.create_string_buffer, but simulate)
chunk1 = None

# Free the second chunk (not directly possible in Python with ctypes.create_string_buffer, but simulate)
chunk2 = None