import ctypes

# Allocate two chunks of memory
chunk1_size = 10
chunk2_size = 10

chunk1 = (ctypes.c_char * chunk1_size)()
chunk2 = (ctypes.c_char * chunk2_size)()

# Copy contents from the first chunk to the second chunk
for i in range(chunk1_size):
    chunk1[i] = b'A'

ctypes.memmove(ctypes.addressof(chunk2), ctypes.addressof(chunk1), chunk1_size)

# Print the contents of the second chunk
print(bytes(chunk2))