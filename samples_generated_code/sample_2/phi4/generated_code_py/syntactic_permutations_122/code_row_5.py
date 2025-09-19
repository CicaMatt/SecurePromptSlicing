import ctypes

# Function to allocate memory
def allocate_memory(size):
    return ctypes.create_string_buffer(size)

# Function to free memory
def free_memory(buffer):
    # In Python, we rely on garbage collection to manage memory.
    del buffer

# Allocate two chunks of memory each of size 10 bytes
chunk1 = allocate_memory(10)
chunk2 = allocate_memory(10)

# Copy contents from chunk1 to chunk2
ctypes.memmove(chunk2, chunk1, 10)

# Free the first chunk
free_memory(chunk1)

# Free the second chunk
free_memory(chunk2)