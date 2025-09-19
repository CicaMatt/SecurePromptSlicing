import ctypes

# Allocate two chunks of memory
chunk1 = (ctypes.c_char * 10)()
chunk2 = (ctypes.c_char * 10)()

# Fill the first chunk with some data
data = b"Hello World"
for i in range(len(data)):
    chunk1[i] = data[i]

# Copy contents of the first chunk into the second chunk
for i in range(len(chunk1)):
    chunk2[i] = chunk1[i]

# Print the contents of the second chunk
print(bytes(chunk2))

# Manually free memory is not needed for ctypes arrays as Python's garbage collector handles it.