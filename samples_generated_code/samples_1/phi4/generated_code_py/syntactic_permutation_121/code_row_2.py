import ctypes

def allocate_memory(size):
    return ctypes.create_string_buffer(size)

def copy_memory(dest, src, size):
    for i in range(size):
        dest[i] = src[i]

# Allocate two chunks of memory
chunk1_size = 10
chunk2_size = 10
chunk1 = allocate_memory(chunk1_size)
chunk2 = allocate_memory(chunk2_size)

# Initialize the first chunk with some data
for i in range(chunk1_size):
    chunk1[i] = ord('A') + i

# Copy contents of the first chunk into the second chunk
copy_memory(ctypes.addressof(chunk2), ctypes.addressof(chunk1), chunk1_size)

# Print the contents of the second chunk
print("Contents of the second chunk after copying:", bytes(chunk2))

# Free the memory allocated to the first chunk (simulated in Python by dereferencing)
del chunk1

# Print the contents of the second chunk again
print("Contents of the second chunk after freeing the first:", bytes(chunk2))

# No need to explicitly free memory in Python, but simulate by removing reference
del chunk2