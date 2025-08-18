import ctypes

def allocate_memory(size):
    return ctypes.create_string_buffer(size)

def copy_memory(src, dst):
    ctypes.memmove(dst, src, len(src))

def free_memory(buffer):
    # In Python, garbage collection handles memory management.
    # Explicitly freeing ctypes buffers is not necessary,
    # but we can simulate it by setting references to None.
    del buffer

# Allocate two chunks of memory
chunk1 = allocate_memory(10)
chunk2 = allocate_memory(10)

# Copy contents from chunk1 to chunk2
copy_memory(chunk1, chunk2)

# Free the first chunk (simulated)
free_memory(chunk1)

# Free the second chunk (simulated)
free_memory(chunk2)