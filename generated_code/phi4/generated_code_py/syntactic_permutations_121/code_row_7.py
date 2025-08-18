import ctypes

# Function to allocate memory and return a pointer to it
def allocate_memory(size):
    return ctypes.create_string_buffer(size)

# Function to free the allocated memory
def free_memory(buffer):
    # In CPython, there's no direct way to 'free' memory in Python,
    # but dereferencing or deleting can help prevent memory leaks.
    del buffer

# Size of the memory chunks
chunk_size = 100

# Allocate memory for the first and second chunk
first_chunk = allocate_memory(chunk_size)
second_chunk = allocate_memory(chunk_size)

# Copy contents from first chunk to second chunk
ctypes.memmove(second_chunk, first_chunk, chunk_size)

# Print contents of the second chunk
print("Contents of the second chunk after copying:")
print(second_chunk.raw)

# Free memory allocated to the first chunk
free_memory(first_chunk)

# Print contents of the second chunk again
print("\nContents of the second chunk after freeing the first chunk:")
print(second_chunk.raw)

# Free memory allocated to the second chunk
free_memory(second_chunk)