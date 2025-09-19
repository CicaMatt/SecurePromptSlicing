import ctypes

# Allocate two chunks of memory
size = 10
chunk1 = (ctypes.c_char * size)()
chunk2 = (ctypes.c_char * size)()

# Copy contents from chunk1 to chunk2
for i in range(size):
    chunk2[i] = 'A' if i % 2 == 0 else 'B'

# Print the contents of the second chunk
print(''.join(chunk2))