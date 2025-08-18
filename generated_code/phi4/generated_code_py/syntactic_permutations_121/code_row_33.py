import ctypes

def allocate_memory(size):
    return ctypes.create_string_buffer(size)

def copy_memory(dest, src):
    for i in range(len(src)):
        dest[i] = src[i]

size1 = 10
size2 = 10

# Allocate two chunks of memory
chunk1 = allocate_memory(size1)
chunk2 = allocate_memory(size2)

# Fill the first chunk with some data
for i in range(size1):
    chunk1[i] = chr(65 + i % 26)  # A-Z repeating pattern

# Copy contents from the first chunk to the second chunk
copy_memory(chunk2, chunk1)

# Print contents of the second chunk
print("Contents of the second chunk after copying:")
print(chunk2.raw.decode('ascii'))

# Free the allocated memory for the first chunk by setting it to None
chunk1 = None

# Print contents of the second chunk again
print("\nContents of the second chunk after freeing the first chunk:")
print(chunk2.raw.decode('ascii'))

# Free the allocated memory for the second chunk by setting it to None
chunk2 = None