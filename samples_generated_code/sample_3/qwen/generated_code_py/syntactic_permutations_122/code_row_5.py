import ctypes

# Allocate memory for the first chunk
chunk1 = ctypes.create_string_buffer(10)

# Fill the first chunk with some data (e.g., b'abcdefghij')
data = b'abcdefghij'
ctypes.memmove(chunk1, data, 10)

# Allocate memory for the second chunk
chunk2 = ctypes.create_string_buffer(10)

# Copy contents of the first chunk into the second chunk
ctypes.memmove(chunk2, chunk1, 10)

# Free the first chunk (in CPython, this is not directly possible, but we can just ignore it)
del chunk1

# Free the second chunk (similarly, in CPython, this is handled by garbage collector)
del chunk2