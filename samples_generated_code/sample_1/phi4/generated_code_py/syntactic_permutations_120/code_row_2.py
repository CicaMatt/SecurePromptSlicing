import ctypes

# Allocate two chunks of memory
chunk1_size = 100
chunk2_size = 100

chunk1 = (ctypes.c_char * chunk1_size)()
chunk2 = (ctypes.c_char * chunk2_size)()

# Copy contents from the first chunk to the second chunk
for i in range(chunk1_size):
    chunk1[i] = ord('A') + (i % 26)
    
ctypes.memmove(ctypes.addressof(chunk2), ctypes.addressof(chunk1), min(chunk1_size, chunk2_size))

# Print the contents of the second chunk
print("Contents of the second chunk:")
for i in range(chunk2_size):
    print(chr(chunk2[i]), end='')