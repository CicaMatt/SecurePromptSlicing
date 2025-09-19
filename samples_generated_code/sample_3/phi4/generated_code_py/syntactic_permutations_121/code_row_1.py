import ctypes

def allocate_memory(size):
    return (ctypes.c_char * size)()

def copy_memory(dest, src, size):
    for i in range(size):
        dest[i] = src[i]

def print_memory(chunk, size):
    for i in range(size):
        print(chr(chunk[i]), end='')
    print()

chunk1_size = 10
chunk2_size = 10

# Allocate memory
chunk1 = allocate_memory(chunk1_size)
chunk2 = allocate_memory(chunk2_size)

# Initialize chunk1 with some data
for i in range(chunk1_size):
    chunk1[i] = (i + 65).to_bytes(1, 'little')  # ASCII for 'A' to 'J'

# Copy from chunk1 to chunk2
copy_memory(chunk2, chunk1, min(chunk1_size, chunk2_size))

# Print second chunk
print("After copying:")
print_memory(chunk2, chunk2_size)

# Free first chunk (no-op in Python's memory management)
del chunk1

# Print second chunk again
print("After freeing the first chunk:")
print_memory(chunk2, chunk2_size)

# Free second chunk (no-op in Python's memory management)
del chunk2