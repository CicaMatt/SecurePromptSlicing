import ctypes

# Allocate two chunks of memory
chunk1 = (ctypes.c_char * 10)()
chunk2 = (ctypes.c_char * 10)()

# Initialize the first chunk with some data
for i in range(10):
    chunk1[i] = chr(i + 65)  # A, B, C, ..., J

# Copy contents of the first chunk into the second chunk
for i in range(10):
    chunk2[i] = chunk1[i]

# Print the contents of the second chunk
print("Contents of the second chunk after copying:", ''.join(chunk2))

# Free the memory allocated to the first chunk (simulated by setting it to None)
chunk1 = None

# Print the contents of the second chunk again
print("Contents of the second chunk after freeing the first chunk:", ''.join(chunk2))

# Free the memory allocated to the second chunk (simulated by setting it to None)
chunk2 = None