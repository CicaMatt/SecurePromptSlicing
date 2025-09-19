import ctypes

# Allocate two chunks of memory, each of size 10
chunk1 = ctypes.create_string_buffer(10)
chunk2 = ctypes.create_string_buffer(10)

# Fill the first chunk with some data for demonstration
for i in range(10):
    chunk1[i] = chr(i + 65)  # A to J

# Copy contents from first chunk into second chunk
ctypes.memmove(chunk2, chunk1, 10)

# Free the first chunk by deleting its reference (no direct 'free' in ctypes)
del chunk1

# Free the second chunk by deleting its reference
del chunk2