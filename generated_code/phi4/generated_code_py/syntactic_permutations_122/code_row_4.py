import ctypes

# Allocate two chunks of memory, each of size 10 bytes
chunk1 = (ctypes.c_char * 10)()
chunk2 = (ctypes.c_char * 10)()

# Fill the first chunk with some data
for i in range(10):
    chunk1[i] = chr(65 + i)  # 'A' to 'J'

# Copy the contents of the first chunk into the second chunk
ctypes.memmove(ctypes.addressof(chunk2), ctypes.addressof(chunk1), 10)

# Free the memory (not necessary in Python as it uses garbage collection, but demonstrating manual deallocation)
del chunk1
del chunk2

# Verify the content copied to the second chunk
for i in range(10):
    print(chr(chunk2[i]), end='')