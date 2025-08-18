import ctypes

# Allocate first chunk of memory
size = 10
chunk1 = (ctypes.c_char * size)()
for i in range(size):
    chunk1[i] = chr(65 + i).encode()  # Fill with ASCII values for A to J

# Allocate second chunk of memory
chunk2 = (ctypes.c_char * size)()

# Copy contents from first chunk to second chunk
ctypes.memmove(chunk2, chunk1, size)

# Print the contents of the second chunk
print(''.join(chunk2).decode())