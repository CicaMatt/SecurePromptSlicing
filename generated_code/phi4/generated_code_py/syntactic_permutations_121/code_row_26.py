import ctypes

# Allocate two chunks of memory
size = 10
chunk1 = (ctypes.c_char * size)()
chunk2 = (ctypes.c_char * size)()

# Initialize the first chunk with some data
for i in range(size):
    chunk1[i] = chr(65 + i).encode('utf-8')

# Copy contents of the first chunk into the second chunk
chunk2[:] = chunk1[:]

# Print the contents of the second chunk
print("Contents of the second chunk after copying:", b''.join(chunk2))

# Free the memory allocated to the first chunk (in Python, garbage collection handles this)
del chunk1

# Print the contents of the second chunk again
print("Contents of the second chunk after freeing first chunk's memory:", b''.join(chunk2))

# Free the memory allocated to the second chunk
del chunk2