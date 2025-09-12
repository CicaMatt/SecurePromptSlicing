import ctypes

def allocate_memory(size):
    return ctypes.create_string_buffer(size)

def copy_memory(dest, src, size):
    ctypes.memmove(dest, src, size)

def free_memory(buffer):
    # In Python, garbage collection handles deallocation,
    # but we can explicitly nullify the reference to simulate 'freeing'.
    buffer = None

# Allocate two chunks of memory each of size 10
chunk1 = allocate_memory(10)
chunk2 = allocate_memory(10)

# Copy contents from first chunk to second chunk
copy_memory(chunk2, chunk1, 10)

# Free the first chunk (simulated by nullifying reference)
free_memory(chunk1)

# Free the second chunk (simulated by nullifying reference)
free_memory(chunk2)