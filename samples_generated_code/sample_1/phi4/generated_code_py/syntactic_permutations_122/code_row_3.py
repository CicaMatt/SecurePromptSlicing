import ctypes

# Allocate two chunks of memory, each of size 10 bytes
chunk1 = (ctypes.c_char * 10)()
chunk2 = (ctypes.c_char * 10)()

# Fill the first chunk with data
for i in range(10):
    chunk1[i] = ord('A') + i

# Copy contents of the first chunk into the second chunk
for i in range(10):
    chunk2[i] = chunk1[i]

# Free the first chunk (in ctypes, we don't explicitly free memory)
del chunk1  # This will allow Python's garbage collector to handle it

# Normally, explicit freeing is not necessary with ctypes in this context,
# but if you need to manually manage resources, use `ctypes` or similar libraries.