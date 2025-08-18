import ctypes

def allocate_memory(size):
    return ctypes.create_string_buffer(size)

def copy_memory(src, dest):
    ctypes.memmove(dest, src, len(src))

def free_memory(buffer):
    # In Python, garbage collection handles freeing memory automatically.
    del buffer

# Allocate two chunks of memory
chunk1 = allocate_memory(10)
chunk2 = allocate_memory(10)

# Initialize the first chunk with some data
initial_data = b'HelloWorld'
ctypes.memmove(chunk1, initial_data, len(initial_data))

# Copy contents from the first chunk to the second
copy_memory(chunk1, chunk2)

# Print the contents of both chunks
print("Chunk 1:", chunk1.raw)
print("Chunk 2:", chunk2.raw)

# Free memory allocated for the first chunk (handled by garbage collection)
free_memory(chunk1)

# Free memory allocated for the second chunk (handled by garbage collection)
free_memory(chunk2)