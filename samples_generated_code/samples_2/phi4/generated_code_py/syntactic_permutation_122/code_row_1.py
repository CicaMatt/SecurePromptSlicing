import ctypes

def allocate_memory(size):
    return (ctypes.c_int * size)()

def copy_memory(source, destination):
    for i in range(len(destination)):
        destination[i] = source[i]

def free_memory(memory_block):
    del memory_block

# Allocate two chunks of memory each of size 10
chunk1 = allocate_memory(10)
chunk2 = allocate_memory(10)

# Initialize the first chunk with some values (for demonstration purposes)
for i in range(len(chunk1)):
    chunk1[i] = i + 1

# Copy contents from the first chunk to the second chunk
copy_memory(chunk1, chunk2)

# Free the memory allocated for the chunks
free_memory(chunk1)
free_memory(chunk2)