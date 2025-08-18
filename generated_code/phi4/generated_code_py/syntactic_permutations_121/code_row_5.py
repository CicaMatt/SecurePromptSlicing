import ctypes

def allocate_chunk(size):
    return (ctypes.c_char * size)()

def copy_memory(destination, source, size):
    for i in range(size):
        destination[i] = source[i]

# Allocate first and second chunks
first_chunk = allocate_chunk(10)
second_chunk = allocate_chunk(10)

# Set contents of the first chunk
for i in range(10):
    first_chunk[i] = ord('A' + i % 26)  # Fill with A, B, C, ..., J

# Copy contents from the first chunk to the second chunk
copy_memory(second_chunk, first_chunk, 10)

# Print contents of the second chunk
print("Contents of the second chunk after copying:", bytes(second_chunk))

# Simulate freeing memory (Python garbage collection will handle this)
del first_chunk

# Print contents of the second chunk again
print("Contents of the second chunk after deleting the first chunk:", bytes(second_chunk))

# Free the second chunk explicitly
del second_chunk