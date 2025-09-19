import ctypes

# Allocate two chunks of memory, each of size 10 bytes
chunk1 = (ctypes.c_char * 10)()
chunk2 = (ctypes.c_char * 10)()

# Fill the first chunk with some data
for i in range(10):
    chunk1[i] = chr((i % 26) + ord('a'))

# Copy contents of the first chunk to the second chunk
for i in range(10):
    chunk2[i] = chunk1[i]

# Function to free memory (in ctypes, we don't need explicit deallocation)
def free_chunk(chunk):
    # In ctypes, there's no manual freeing required as Python handles garbage collection.
    pass

# "Free" the first chunk
free_chunk(chunk1)

# "Free" the second chunk
free_chunk(chunk2)