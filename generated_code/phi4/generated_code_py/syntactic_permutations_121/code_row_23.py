import ctypes

def allocate_memory(size):
    return ctypes.create_string_buffer(size)

def copy_memory(dest, src, size):
    ctypes.memmove(dest, src, size)

def free_memory(buffer):
    # In Python with ctypes, memory is automatically managed and does not require explicit freeing.
    pass

# Allocate two chunks of memory
size = 10
chunk1 = allocate_memory(size)
chunk2 = allocate_memory(size)

# Fill the first chunk with some data (e.g., 'Hello')
ctypes.memmove(chunk1, b'Hello', len(b'Hello'))

# Copy contents of the first chunk into the second chunk
copy_memory(chunk2, chunk1, size)

# Print the contents of the second chunk
print("Contents of second chunk:", chunk2.raw[:5])

# Free the memory (no-op in Python, as garbage collection handles it)
free_memory(chunk1)

# Attempt to print the contents of the second chunk again
# Note: Even though we "free" chunk1, the data is still accessible until all references are gone.
print("Contents of second chunk after freeing first:", chunk2.raw[:5])

# Free the memory allocated for the second chunk (again no-op in Python)
free_memory(chunk2)

# Attempt to print contents again to demonstrate no further access
try:
    print("Attempt to access freed memory:", chunk2.raw[:5])
except ValueError as e:
    print(e)  # ctypes doesn't raise an error directly, just a demonstration of what would happen if we could