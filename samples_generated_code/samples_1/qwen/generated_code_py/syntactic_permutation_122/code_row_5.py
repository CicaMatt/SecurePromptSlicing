import ctypes

# Allocate two chunks of memory, each of size 10 bytes
chunk1 = ctypes.create_string_buffer(10)
chunk2 = ctypes.create_string_buffer(10)

# Fill chunk1 with some data (example: b'abcdefghij')
chunk1.raw = b'abcdefghij'

# Copy the contents from chunk1 to chunk2
ctypes.memmove(chunk2, chunk1, 10)

# Free the first chunk (not needed in ctypes as it handles memory management)
# but for demonstration, setting the buffer to None
chunk1 = None

# Free the second chunk
chunk2 = None