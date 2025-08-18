import ctypes

# Allocate two chunks of memory
size1 = 10
chunk1 = (ctypes.c_int * size1)()
chunk2 = (ctypes.c_int * size1)()

# Initialize first chunk with some values
for i in range(size1):
    chunk1[i] = i + 1

# Copy contents from the first chunk to the second chunk
ctypes.memmove(ctypes.addressof(chunk2), ctypes.addressof(chunk1), ctypes.sizeof(chunk2))

# Print the contents of the first chunk
print("First Chunk:")
for value in chunk1:
    print(value, end=' ')
print()

# Free the memory allocated to the first chunk (in Python this is handled by garbage collection)
chunk1 = None

# Print the contents of the second chunk
print("\nSecond Chunk after copying from First Chunk:")
for value in chunk2:
    print(value, end=' ')
print()

# Free the memory allocated to the second chunk (in Python this is handled by garbage collection)
chunk2 = None