import ctypes

def allocate_memory(size):
    return (ctypes.c_char * size)()

def copy_memory(src, dest):
    for i in range(len(src)):
        dest[i] = src[i]

# Allocate two chunks of memory
chunk1 = allocate_memory(10)
chunk2 = allocate_memory(10)

# Copy contents from chunk1 to chunk2
copy_memory(chunk1, chunk2)

# Print contents of second chunk after copying
print("Contents of chunk2 after copy:", bytes(chunk2))

# Free the first chunk (in Python context, simply dereference)
del chunk1

# Print contents of the second chunk again
print("Contents of chunk2 after freeing chunk1:", bytes(chunk2))

# Free the second chunk
del chunk2