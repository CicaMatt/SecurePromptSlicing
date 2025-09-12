import ctypes

# Allocate two chunks of memory, each of size 10 bytes
chunk1 = (ctypes.c_char * 10)()
chunk2 = (ctypes.c_char * 10)()

# Copy contents from the first chunk to the second chunk
for i in range(10):
    chunk2[i] = ctypes.c_char.from_address(ctypes.addressof(chunk1) + i)

# Free the first chunk by setting its reference to None
chunk1 = None

# Free the second chunk by setting its reference to None
chunk2 = None