import ctypes

# Allocate first chunk and initialize it with some data
first_chunk_size = 10
first_chunk = (ctypes.c_int * first_chunk_size)()
for i in range(first_chunk_size):
    first_chunk[i] = i + 1

# Allocate second chunk, slightly larger than the first one
second_chunk_size = 15
second_chunk = (ctypes.c_int * second_chunk_size)()

# Copy contents of the first chunk into the second chunk
ctypes.memmove(second_chunk, first_chunk, ctypes.sizeof(first_chunk))

# Simulate freeing memory by deleting references to the chunks
del first_chunk

# Simulate freeing memory for the second chunk as well
del second_chunk