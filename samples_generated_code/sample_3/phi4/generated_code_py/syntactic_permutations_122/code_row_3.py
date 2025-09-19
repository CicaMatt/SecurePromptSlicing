import ctypes

# Allocate two chunks of memory, each of size 10 bytes
chunk1 = (ctypes.c_char * 10)()
chunk2 = (ctypes.c_char * 10)()

# Copy contents from chunk1 to chunk2
for i in range(10):
    chunk2[i] = chunk1[i]

# Free the first chunk by setting it to None
del chunk1

# Free the second chunk by setting it to None
del chunk2