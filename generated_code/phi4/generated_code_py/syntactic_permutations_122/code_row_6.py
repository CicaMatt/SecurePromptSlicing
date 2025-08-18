import ctypes

def allocate_chunk(size):
    return (ctypes.c_char * size)()

def copy_contents(src, dest):
    for i in range(len(dest)):
        dest[i] = src[i]

def free_chunk(chunk):
    del chunk

# Allocate two chunks each of size 10
chunk1 = allocate_chunk(10)
chunk2 = allocate_chunk(10)

# Copy contents from the first chunk to the second chunk
copy_contents(chunk1, chunk2)

# Free the first chunk
free_chunk(chunk1)

# Free the second chunk
free_chunk(chunk2)