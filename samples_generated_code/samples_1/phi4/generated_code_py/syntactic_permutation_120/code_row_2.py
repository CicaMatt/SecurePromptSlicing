import ctypes

# Allocate two chunks of memory
size = 10
chunk1 = (ctypes.c_int * size)()
chunk2 = (ctypes.c_int * size)()

# Initialize the first chunk with some values
for i in range(size):
    chunk1[i] = i + 1

# Copy contents from the first chunk to the second chunk
ctypes.memmove(ctypes.addressof(chunk2), ctypes.addressof(chunk1), ctypes.sizeof(chunk2))

# Print the contents of the second chunk
for value in chunk2:
    print(value)