import ctypes

def allocate_memory(size):
    return ctypes.create_string_buffer(size)

def copy_memory(dest, src, size):
    for i in range(size):
        dest[i] = src[i]

def free_memory(buffer):
    del buffer

# Allocate two chunks of memory each of size 10
chunk1 = allocate_memory(10)
chunk2 = allocate_memory(10)

# Copy contents from the first chunk to the second chunk
copy_memory(chunk2, chunk1, 10)

# Free the first chunk
free_memory(chunk1)

# Free the second chunk
free_memory(chunk2)