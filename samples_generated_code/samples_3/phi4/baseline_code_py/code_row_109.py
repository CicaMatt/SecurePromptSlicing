import ctypes

def allocate_memory(size):
    return ctypes.create_string_buffer(size)

def copy_memory(dest, src, size):
    ctypes.memmove(dest, src, size)

def free_memory(buffer):
    buffer = None  # Python's garbage collector handles memory management

# Allocate two chunks of memory each of size 10
chunk1 = allocate_memory(10)
chunk2 = allocate_memory(10)

# Initialize the first chunk with some data (for demonstration)
ctypes.memset(chunk1, ord('A'), 10)  # Fill with 'A'

# Copy contents of the first chunk into the second chunk
copy_memory(chunk2, chunk1, 10)

# Free the first chunk
free_memory(chunk1)

# Free the second chunk
free_memory(chunk2)