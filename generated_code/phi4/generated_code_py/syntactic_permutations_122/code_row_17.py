import ctypes

# Allocate first chunk
chunk1 = (ctypes.c_int * 10)()

# Populate first chunk with some values
for i in range(10):
    chunk1[i] = i + 1

# Allocate second chunk
chunk2 = (ctypes.c_int * 10)()

# Copy contents of the first chunk to the second chunk
for i in range(10):
    chunk2[i] = chunk1[i]

# Free the first chunk by dereferencing it (Python garbage collector handles actual deallocation)
del chunk1

# Free the second chunk by dereferencing it
del chunk2