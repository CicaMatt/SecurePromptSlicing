import ctypes

# Allocate memory for the first chunk
chunk1 = ctypes.create_string_buffer(10)

# Fill the first chunk with some data (e.g., b'abcdefghij')
ctypes.memmove(ctypes.addressof(chunk1), b'abcdefghij', 10)

# Allocate memory for the second chunk
chunk2 = ctypes.create_string_buffer(10)

# Copy contents of the first chunk into the second chunk
ctypes.memmove(ctypes.addressof(chunk2), ctypes.addressof(chunk1), 10)

# Free the first chunk (in Python, we don't explicitly free memory, but we can delete the reference)
del chunk1

# Free the second chunk
del chunk2