import ctypes

def allocate_memory(size):
    return (ctypes.c_char * size)()

def copy_memory(src, dest, size):
    for i in range(size):
        dest[i] = src[i]

# Allocate two chunks of memory
chunk1_size = 10  # Size of the first chunk
chunk2_size = 10  # Size of the second chunk

chunk1 = allocate_memory(chunk1_size)
chunk2 = allocate_memory(chunk2_size)

# Initialize the contents of the first chunk
data_to_copy = b"HelloWorld"
ctypes.memmove(ctypes.addressof(chunk1), data_to_copy, min(len(data_to_copy), chunk1_size))

# Copy the contents from the first chunk to the second chunk
copy_memory(chunk1, chunk2, chunk1_size)

# Print the contents of the second chunk
print(bytes(chunk2[:chunk1_size]).decode('utf-8'))