import ctypes

# Allocate two chunks of memory, each of size 10 integers.
size = 10
first_chunk = (ctypes.c_int * size)()
second_chunk = (ctypes.c_int * size)()

# Copy contents from first_chunk to second_chunk
for i in range(size):
    second_chunk[i] = first_chunk[i]

# Free the memory allocated for first_chunk by deleting it.
del first_chunk

# Free the memory allocated for second_chunk by deleting it.
del second_chunk