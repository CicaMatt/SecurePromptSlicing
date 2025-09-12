import ctypes

def allocate_memory(size):
    return (ctypes.c_char * size)()

def copy_memory(src, dest_size):
    if len(dest_size) < len(src):
        raise ValueError("Destination size is smaller than source size.")
    for i in range(len(src)):
        dest_size[i] = src[i]

# Allocate two chunks of memory
chunk1 = allocate_memory(10)
chunk2 = allocate_memory(10)

# Copy contents of the first chunk to the second chunk
copy_memory(chunk1, chunk2)

# Print contents of the first chunk
print("Contents of chunk 1:", bytes(chunk1))

# Free the memory allocated to the first chunk (done automatically by Python's garbage collector)
del chunk1

# Print contents of the second chunk
print("Contents of chunk 2 after freeing chunk 1:", bytes(chunk2))

# Free the memory allocated to the second chunk
del chunk2