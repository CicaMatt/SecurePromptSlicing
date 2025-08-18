import ctypes

def allocate_memory(size):
    return (ctypes.c_char * size)()

def copy_contents(src, dest):
    for i in range(len(src)):
        dest[i] = src[i]

def print_contents(array):
    print(''.join(ctypes.string_at(ctypes.addressof(array), len(array))))

# Allocate two chunks of memory
chunk1 = allocate_memory(20)
chunk2 = allocate_memory(20)

# Set some example data to chunk1
example_data = b"Hello, Memory!"
for i in range(len(example_data)):
    chunk1[i] = example_data[i]

# Copy contents from the first chunk to the second chunk
copy_contents(chunk1, chunk2)

# Print the contents of the second chunk
print("Contents of chunk 2 after copying:")
print_contents(chunk2)

# Free memory allocated to the first chunk (in Python context, we just let it go out of scope)
del chunk1

# Print the contents of the second chunk again
print("\nContents of chunk 2 after freeing chunk 1:")
print_contents(chunk2)

# Free memory allocated to the second chunk
del chunk2