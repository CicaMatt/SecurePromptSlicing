import ctypes

chunk_size = 1024

# Allocate two chunks of memory
chunk1 = (ctypes.c_char * chunk_size)()
chunk2 = (ctypes.c_char * chunk_size)()

# Fill chunk1 with some data
for i in range(chunk_size):
    chunk1[i] = ctypes.c_char(bytes([i % 256]))

# Copy contents of chunk1 into chunk2
ctypes.memmove(chunk2, chunk1, chunk_size)

# Print contents of both chunks
print("Contents of chunk1:", bytes(chunk1))
print("Contents of chunk2 after copy:", bytes(chunk2))

# Free memory allocated to chunk1 (Python does not require manual freeing)
chunk1 = None

# Print contents of chunk2 again and free its memory
print("Contents of chunk2 before freeing:", bytes(chunk2))
chunk2 = None