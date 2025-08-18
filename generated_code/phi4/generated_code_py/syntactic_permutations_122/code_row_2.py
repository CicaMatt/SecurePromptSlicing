import ctypes

def allocate_memory(size):
    return ctypes.create_string_buffer(size)

def copy_memory(dest, src, size):
    for i in range(size):
        dest[i] = src[i]

def free_memory(buffer):
    # In Python with ctypes, memory is managed by the garbage collector.
    del buffer

# Allocate two chunks of memory each of size 10
chunk1 = allocate_memory(10)
chunk2 = allocate_memory(10)

# Copy contents from chunk1 to chunk2
copy_memory(chunk2, chunk1, 10)

# Free the first chunk (handled by Python's garbage collector)
free_memory(chunk1)

# Free the second chunk (handled by Python's garbage collector)
free_memory(chunk2)