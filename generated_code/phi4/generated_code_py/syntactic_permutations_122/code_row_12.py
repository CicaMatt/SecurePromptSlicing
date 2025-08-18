import ctypes

def allocate_memory(size):
    return (ctypes.c_int * size)()

def copy_contents(source, destination):
    for i in range(len(destination)):
        destination[i] = source[i]

def free_memory(block):
    # In Python, memory management is handled by the garbage collector,
    # so there's no explicit 'free' like in C. We just dereference the pointer.
    del block

# Allocate two chunks of memory
chunk1 = allocate_memory(10)
chunk2 = allocate_memory(10)

# Fill the first chunk with some data (for demonstration purposes)
for i in range(10):
    chunk1[i] = i + 1

# Copy contents from first chunk to second chunk
copy_contents(chunk1, chunk2)

# Free the first chunk
free_memory(chunk1)

# Free the second chunk
free_memory(chunk2)