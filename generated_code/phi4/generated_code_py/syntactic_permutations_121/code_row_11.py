import ctypes

# Allocate two chunks of memory
chunk1 = (ctypes.c_char * 10)()
chunk2 = (ctypes.c_char * 10)()

# Copy data from the first chunk to the second chunk
for i in range(10):
    chunk2[i] = chunk1[i]

# Print contents of the second chunk
print('Contents of the second chunk:', b''.join(chunk2))

# Free the memory allocated to the first chunk (simulated)
del chunk1

# Print contents of the second chunk again
print('Contents of the second chunk after freeing the first:', b''.join(chunk2))

# Free the memory allocated to the second chunk (simulated)
del chunk2