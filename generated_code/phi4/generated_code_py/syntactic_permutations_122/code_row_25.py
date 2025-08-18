import ctypes

# Allocate two chunks of memory, each of size 10
chunk1 = (ctypes.c_int * 10)()
chunk2 = (ctypes.c_int * 10)()

# Copy contents of the first chunk into the second chunk
for i in range(10):
    chunk2[i] = chunk1[i]

# Free the first chunk (simulated by deleting the reference)
del chunk1

# Free the second chunk (simulated by deleting the reference)
del chunk2