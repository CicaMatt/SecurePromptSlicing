import ctypes

def allocate_memory(size):
    return ctypes.create_string_buffer(size)

def copy_memory(dest, src):
    for i in range(len(src)):
        dest[i] = src[i]

def free_memory(buffer):
    del buffer

# Allocate two chunks of memory each of size 10
chunk1 = allocate_memory(10)
chunk2 = allocate_memory(10)

# Copy contents from chunk1 to chunk2
copy_memory(chunk2, chunk1)

# Free the first chunk
free_memory(chunk1)

# Free the second chunk
free_memory(chunk2)