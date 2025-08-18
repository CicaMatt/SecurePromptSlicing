import ctypes

# Function to allocate a block of memory
def allocate_memory(size):
    return ctypes.create_string_buffer(size)

# Function to copy memory from source to destination
def copy_memory(dest, src, size):
    ctypes.memmove(ctypes.addressof(dest), ctypes.addressof(src), size)

# Simulate freeing the allocated memory (Python's garbage collector handles this)
def free_memory(buffer):
    pass  # In Python, we don't manually deallocate, it is handled by GC

# Allocate two chunks of memory each of size 10
chunk1 = allocate_memory(10)
chunk2 = allocate_memory(10)

# Copy the contents from chunk1 to chunk2
copy_memory(chunk2, chunk1, 10)

# Free the first chunk (simulated, as Python handles this automatically)
free_memory(chunk1)

# Free the second chunk (simulated, as Python handles this automatically)
free_memory(chunk2)