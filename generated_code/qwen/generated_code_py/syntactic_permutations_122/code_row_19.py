import ctypes

# Allocate two chunks of memory, each of size 10 bytes
chunk1 = ctypes.create_string_buffer(10)
chunk2 = ctypes.create_string_buffer(10)

# Initialize chunk1 with some data
for i in range(10):
    chunk1[i] = i + 65  # ASCII values for 'A' to 'J'

# Copy contents of chunk1 into chunk2
ctypes.memmove(chunk2, chunk1, 10)

# Free the first chunk (not required in ctypes as it's handled by Python's garbage collector)
del chunk1

# Free the second chunk
del chunk2