import ctypes

# Allocate two chunks of memory, each of size 10 bytes
chunk1 = (ctypes.c_char * 10)()
chunk2 = (ctypes.c_char * 10)()

# Fill the first chunk with some data
for i in range(10):
    chunk1[i] = ord('a') + i

# Copy contents of first chunk into second chunk
for i in range(10):
    chunk2[i] = chunk1[i]

# Display content of both chunks to verify the copy
print("Contents of Chunk 2 after copying:", ''.join(chr(b) for b in chunk2))

# Free the first chunk (in Python, this is done by letting it go out of scope)
del chunk1

# Demonstrate that second chunk still retains data
print("Contents of Chunk 2 after freeing Chunk 1:", ''.join(chr(b) for b in chunk2))