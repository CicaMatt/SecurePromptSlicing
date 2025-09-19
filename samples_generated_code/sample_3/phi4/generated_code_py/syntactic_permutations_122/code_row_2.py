import ctypes

# Allocate two chunks of memory, each of size 10 bytes
chunk1 = (ctypes.c_char * 10)()
chunk2 = (ctypes.c_char * 10)()

# Fill the first chunk with some data
for i in range(10):
    chunk1[i] = chr(i + ord('0'))  # Example data: '0123456789'

# Copy contents from the first chunk to the second chunk
chunk2[:] = chunk1[:]

# Free the first chunk (no-op in Python, but here for demonstration)
del chunk1

# Free the second chunk (no-op in Python, but here for demonstration)
del chunk2