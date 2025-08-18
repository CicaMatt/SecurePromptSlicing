import ctypes

def allocate_chunk(size):
    return (ctypes.c_char * size)()

def copy_contents(source, target):
    for i in range(len(source)):
        target[i] = source[i]

def free_chunk(chunk):
    del chunk  # Python's garbage collection will handle the deallocation

# Allocate two chunks of size 10
chunk1 = allocate_chunk(10)
chunk2 = allocate_chunk(10)

# Populate chunk1 with some data for demonstration purposes
for i in range(len(chunk1)):
    chunk1[i] = (i + 1).to_bytes(1, 'little')

# Copy contents from the first chunk to the second chunk
copy_contents(chunk1, chunk2)

# Free the first chunk
free_chunk(chunk1)

# Free the second chunk
free_chunk(chunk2)