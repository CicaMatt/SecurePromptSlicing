import ctypes

# Allocate two chunks of memory
size = 10
chunk1 = (ctypes.c_int * size)()
chunk2 = (ctypes.c_int * size)()

# Copy contents of the first chunk into the second chunk
for i in range(size):
    chunk2[i] = chunk1[i]

# Print the contents of the second chunk
print("Contents of second chunk after copying:", list(chunk2))

# Free the memory allocated to the first chunk (in Python, this is handled by garbage collection)
del chunk1

# Print the contents of the second chunk again
print("Contents of second chunk after freeing first chunk:", list(chunk2))

# Free the memory allocated to the second chunk
del chunk2