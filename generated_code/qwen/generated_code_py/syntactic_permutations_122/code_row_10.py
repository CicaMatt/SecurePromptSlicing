import ctypes

# Allocate two chunks of memory
chunk1 = ctypes.create_string_buffer(1024)  # 1 KB
chunk2 = ctypes.create_string_buffer(1024)  # 1 KB

# Fill chunk1 with some data
data = b"Hello, World!"
ctypes.memmove(chunk1, data, len(data))

# Copy contents of chunk1 into chunk2
ctypes.memmove(chunk2, chunk1, len(data))

# Free the first chunk (not necessary in Python as ctypes does not manage memory allocation directly)
del chunk1

# Free the second chunk (not necessary in Python as ctypes does not manage memory allocation directly)
del chunk2