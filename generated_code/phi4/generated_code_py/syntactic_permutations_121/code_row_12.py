import ctypes

def allocate_memory(size):
    return ctypes.create_string_buffer(size)

def copy_memory(dest, src, size):
    for i in range(size):
        dest[i] = src[i]

def print_memory(buffer, size):
    print(buffer.raw[:size].decode('utf-8'))

# Allocate two chunks of memory
chunk1_size = 10
chunk2_size = 10

chunk1 = allocate_memory(chunk1_size)
chunk2 = allocate_memory(chunk2_size)

# Copy the content of the first chunk into the second chunk
copy_memory(chunk2, chunk1, chunk1_size)

# Print the second chunk
print("Second Chunk after copy:")
print_memory(chunk2, chunk2_size)

# Free the memory allocated to the first chunk (no-op in Python)
del chunk1

# Print the second chunk again
print("Second Chunk after freeing first chunk:")
print_memory(chunk2, chunk2_size)

# Free the memory allocated to the second chunk (no-op in Python)
del chunk2