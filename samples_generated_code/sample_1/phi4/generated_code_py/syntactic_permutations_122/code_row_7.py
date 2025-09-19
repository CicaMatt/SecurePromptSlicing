import ctypes

def allocate_memory(size):
    return ctypes.create_string_buffer(size)

def copy_memory(src, dst):
    ctypes.memmove(dst, src, len(src))

def free_memory(memory):
    # In Python, garbage collection is automatic; no explicit free function needed.
    pass  # Just a placeholder for demonstration.

# Allocate two chunks of memory each of size 10
chunk1 = allocate_memory(10)
chunk2 = allocate_memory(10)

# Initialize the first chunk with some data
ctypes.memset(chunk1, ord('A'), len(chunk1))

# Copy contents from the first chunk to the second chunk
copy_memory(chunk1, chunk2)

# Free the first chunk (garbage collected automatically in Python)
free_memory(chunk1)

# Free the second chunk (also garbage collected automatically in Python)
free_memory(chunk2)

# Print the data from the second chunk to verify copying
print(ctypes.string_at(chunk2))