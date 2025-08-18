import ctypes

# Allocate two chunks of memory
chunk1_size = 10
chunk2_size = 10

chunk1 = (ctypes.c_int * chunk1_size)()
chunk2 = (ctypes.c_int * chunk2_size)()

# Copy contents from the first chunk to the second chunk
for i in range(chunk1_size):
    chunk1[i] = i + 1  # Initialize with some values
for i in range(chunk1_size):
    chunk2[i] = chunk1[i]

# Print contents of the second chunk
print("Contents of the second chunk after copying:", list(chunk2))

# Free memory allocated to the first chunk (not directly possible in Python, but we can dereference)
del chunk1

# Print contents of the second chunk again
print("Contents of the second chunk after freeing first chunk:", list(chunk2))

# Free memory allocated to the second chunk
del chunk2