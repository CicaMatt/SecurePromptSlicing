import ctypes

# Allocate two chunks of memory each of size 10 bytes
chunk1 = ctypes.create_string_buffer(10)
chunk2 = ctypes.create_string_buffer(10)

# Fill chunk1 with some data (example: b'abcdefghij')
ctypes.memmove(ctypes.addressof(chunk1), b'abcdefghij', 10)

# Copy the contents of the first chunk into the second
ctypes.memmove(ctypes.addressof(chunk2), ctypes.addressof(chunk1), 10)

# Free the first chunk (not necessary in Python, but simulating)
del chunk1

# Free the second chunk (not necessary in Python, but simulating)
del chunk2