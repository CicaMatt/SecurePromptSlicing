import ctypes

# Allocate two chunks of memory
size = 10
chunk1 = (ctypes.c_char * size)()
chunk2 = (ctypes.c_char * size)()

# Initialize first chunk with some data
for i in range(size):
    chunk1[i] = chr(65 + i).encode()  # Fill with 'A', 'B', ..., 'J'

# Copy contents of the first chunk into the second chunk
for i in range(size):
    chunk2[i] = chunk1[i]

# Print the contents of the second chunk
print("Contents of the second chunk:")
for i in range(size):
    print(chunk2[i].decode(), end=' ')