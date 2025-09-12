import ctypes

def allocate_memory(size):
    return (ctypes.c_char * size)()

def copy_memory(src, dest, size):
    for i in range(size):
        dest[i] = src[i]

def print_memory(data, size):
    print(b''.join([bytes([data[i]]) for i in range(size)]))

# Allocate memory
size = 10
chunk1 = allocate_memory(size)
chunk2 = allocate_memory(size)

# Copy contents of chunk1 into chunk2
copy_memory(chunk1, chunk2, size)

# Print the contents of chunk2
print_memory(chunk2, size)

# Free the memory allocated to the first chunk (simulated by setting it to None)
del chunk1

# Print the contents of chunk2 again
print_memory(chunk2, size)

# Free the memory allocated to the second chunk (simulated by setting it to None)
del chunk2