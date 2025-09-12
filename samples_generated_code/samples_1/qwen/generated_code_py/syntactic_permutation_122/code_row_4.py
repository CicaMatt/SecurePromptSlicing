import ctypes

# Allocate two chunks of memory, each of size 10 bytes
chunk1 = ctypes.create_string_buffer(10)
chunk2 = ctypes.create_string_buffer(10)

# Copy the contents of the first chunk to the second chunk
ctypes.memmove(chunk2, chunk1, 10)

# Free the first chunk (not necessary in Python as memory management is automatic, but we can simulate it by setting to None)
chunk1 = None

# Free the second chunk
chunk2 = None