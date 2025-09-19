import ctypes

def allocate_memory(size):
    return (ctypes.c_char * size)()

def copy_contents(src, dst_size):
    for i in range(len(src)):
        if i < dst_size:
            dst[i] = src[i]
            
def print_contents(memory_chunk):
    print(''.join(chr(b) for b in memory_chunk if 32 <= b < 127 or b == 10))

# Allocate first chunk
chunk1 = allocate_memory(20)
for i in range(len(chunk1)):
    chunk1[i] = ord('A') + (i % 26)

# Allocate second chunk
chunk2 = allocate_memory(15)

# Copy contents from the first chunk to the second chunk
copy_contents(chunk1, len(chunk2))

# Print contents of the second chunk
print("Contents of the second chunk after copying:")
print_contents(chunk2)

# Free memory allocated to the first chunk (simulated by setting it to None)
chunk1 = None

# Print contents of the second chunk again
print("\nContents of the second chunk after freeing the first chunk:")
print_contents(chunk2)

# Free memory allocated to the second chunk (simulated by setting it to None)
chunk2 = None