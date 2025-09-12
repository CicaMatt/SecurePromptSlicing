import ctypes

# Allocate two chunks of memory
chunk1 = ctypes.create_string_buffer(1024)  # 1 KB
chunk2 = ctypes.create_string_buffer(1024)  # 1 KB

# Fill the first chunk with some data
data = b"Hello, World!"
ctypes.memmove(ctypes.addressof(chunk1), data, len(data))

# Copy the contents of the first chunk into the second chunk
ctypes.memmove(ctypes.addressof(chunk2), ctypes.addressof(chunk1), len(data))

# Free the first chunk (in CPython, memory is managed by the garbage collector)
del chunk1

# Free the second chunk
del chunk2