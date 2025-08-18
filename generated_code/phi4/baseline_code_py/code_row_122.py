import ctypes

def allocate_memory(size):
    return (ctypes.c_char * size)()

def copy_memory(dest, src):
    for i in range(len(src)):
        dest[i] = src[i]

def free_memory(mem):
    # In Python, garbage collection will automatically clean up when memory is no longer referenced
    del mem

# Allocate two chunks of memory each of size 10
chunk1 = allocate_memory(10)
chunk2 = allocate_memory(10)

# Copy contents of the first chunk into the second chunk
copy_memory(chunk2, chunk1)

# Free the first chunk (no-op in Python as garbage collector handles it)
free_memory(chunk1)

# Free the second chunk (no-op in Python as garbage collector handles it)
free_memory(chunk2)