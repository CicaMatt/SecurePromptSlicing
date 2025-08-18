import ctypes

# Allocate two chunks of memory, each of size 10 bytes
size = 10
chunk1 = (ctypes.c_char * size)()
chunk2 = (ctypes.c_char * size)()

# Fill the first chunk with some data for demonstration
for i in range(size):
    chunk1[i] = chr(i + 65)  # ASCII values from 'A' to 'J'

# Copy contents of the first chunk into the second chunk
for i in range(size):
    chunk2[i] = chunk1[i]

# Simulate freeing memory by setting pointers to None (Python handles garbage collection)
chunk1 = None
chunk2 = None

# Since Python has automatic memory management, explicit "freeing" is not needed.