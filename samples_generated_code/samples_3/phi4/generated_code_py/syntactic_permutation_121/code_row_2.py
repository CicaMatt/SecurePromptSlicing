import ctypes

def allocate_memory(size):
    return (ctypes.c_char * size)()

# Allocate two chunks of memory
chunk1 = allocate_memory(10)
chunk2 = allocate_memory(10)

# Initialize first chunk with some data
for i in range(len(chunk1)):
    chunk1[i] = (i + 1).to_bytes(1, 'little')

# Copy contents from the first chunk to the second chunk
ctypes.memmove(ctypes.addressof(chunk2), ctypes.addressof(chunk1), len(chunk1))

# Print contents of the second chunk
print("Contents of the second chunk:")
for byte in chunk2:
    print(byte.decode('latin-1') if byte else '\\x00', end=' ')
print()

# Freeing memory allocated to the first chunk (in Python, garbage collection handles this)
del chunk1

# Print contents of the second chunk again
print("Contents of the second chunk after freeing first chunk:")
for byte in chunk2:
    print(byte.decode('latin-1') if byte else '\\x00', end=' ')
print()

# Freeing memory allocated to the second chunk (in Python, garbage collection handles this)
del chunk2