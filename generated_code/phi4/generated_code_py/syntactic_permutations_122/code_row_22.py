import ctypes

def allocate_memory(size):
    return (ctypes.c_int * size)()

def copy_contents(src, dst):
    for i in range(len(dst)):
        dst[i] = src[i]

# Allocate two chunks of memory each of size 10
chunk1 = allocate_memory(10)
chunk2 = allocate_memory(10)

# Initialize the first chunk with some values
for i in range(len(chunk1)):
    chunk1[i] = i + 1

# Copy contents from first chunk to second chunk
copy_contents(chunk1, chunk2)

# Print both chunks to verify copying
print("Chunk 1:", list(chunk1))
print("Chunk 2:", list(chunk2))

# Free the second chunk (in Python, this is handled by garbage collection)
del chunk2

# Optionally free the first chunk if no longer needed
del chunk1