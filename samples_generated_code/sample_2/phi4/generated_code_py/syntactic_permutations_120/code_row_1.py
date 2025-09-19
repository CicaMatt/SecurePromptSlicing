import ctypes

# Allocate two chunks of memory, both 10 bytes in size
chunk1 = (ctypes.c_char * 10)()
chunk2 = (ctypes.c_char * 10)()

# Fill the first chunk with some example data
for i in range(10):
    chunk1[i] = chr((i % 26) + ord('A'))

# Copy contents of the first chunk into the second chunk
for i in range(10):
    chunk2[i] = chunk1[i]

# Print the contents of the second chunk
print("Contents of the second chunk:", b''.join(chunk2).decode())