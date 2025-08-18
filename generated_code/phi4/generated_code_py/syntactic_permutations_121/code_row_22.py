import ctypes

def allocate_memory(size):
    return ctypes.create_string_buffer(size)

def copy_memory(src, dest):
    ctypes.memmove(dest, src, len(src.raw))

def free_memory(buffer):
    del buffer

# Allocate two chunks of memory
chunk1 = allocate_memory(10)
chunk2 = allocate_memory(10)

# Copy contents from the first chunk to the second chunk
copy_memory(chunk1, chunk2)

# Print contents of the second chunk
print("Contents of the second chunk after copy:", chunk2.raw.decode('utf-8', 'ignore'))

# Free allocated memory for the first chunk
free_memory(chunk1)

# Print contents of the second chunk again
print("Contents of the second chunk after freeing first chunk:", chunk2.raw.decode('utf-8', 'ignore'))

# Free allocated memory for the second chunk
free_memory(chunk2)