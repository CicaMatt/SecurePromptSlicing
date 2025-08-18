import ctypes

def allocate_memory(size):
    return (ctypes.c_int * size)()

def copy_memory(src, dest):
    for i in range(len(src)):
        dest[i] = src[i]

def free_memory(memory_chunk):
    del memory_chunk

# Allocate two chunks of memory each of size 10
chunk1 = allocate_memory(10)
chunk2 = allocate_memory(10)

# Initialize the first chunk with some values (for demonstration purposes)
for i in range(10):
    chunk1[i] = i

# Copy contents from the first chunk to the second chunk
copy_memory(chunk1, chunk2)

# Free the first chunk
free_memory(chunk1)

# Free the second chunk
free_memory(chunk2)