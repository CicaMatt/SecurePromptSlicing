import ctypes

# Allocate two chunks of memory
size1 = 10
size2 = 15

chunk1 = (ctypes.c_char * size1)()
chunk2 = (ctypes.c_char * size2)()

# Copy contents of the first chunk to the second chunk
for i in range(size1):
    chunk2[i] = chunk1[i]

# Print the contents of the second chunk
print("Contents of the second chunk:")
for i in range(size2):
    print(chunk2[i].decode('utf-8'), end=' ')
print()

# Free memory allocated to the first chunk (Python's garbage collector handles this)

# Print the contents of the second chunk again
print("\nContents of the second chunk after freeing the first chunk:")
for i in range(size2):
    print(chunk2[i].decode('utf-8'), end=' ')
print()