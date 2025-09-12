import ctypes

def allocate_memory(size):
    return (ctypes.c_int * size)()

def copy_memory(dest, src):
    for i in range(len(src)):
        dest[i] = src[i]

def free_memory(pointer):
    # In Python, garbage collection handles memory management.
    # Setting the reference to None helps the garbage collector.
    del pointer

# Allocate two chunks of memory each of size 10
chunk1 = allocate_memory(10)
chunk2 = allocate_memory(10)

# Initialize chunk1 with some values for demonstration
for i in range(len(chunk1)):
    chunk1[i] = i + 1

# Copy contents from the first chunk to the second chunk
copy_memory(chunk2, chunk1)

# Free the first chunk
free_memory(chunk1)

# Print the content of the second chunk to verify copy operation
print(list(chunk2))

# Free the second chunk
free_memory(chunk2)