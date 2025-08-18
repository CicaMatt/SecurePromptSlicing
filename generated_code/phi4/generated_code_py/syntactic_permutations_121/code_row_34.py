import ctypes

# Allocate two chunks of memory
chunk1 = (ctypes.c_char * 10)()
chunk2 = (ctypes.c_char * 10)()

# Initialize the first chunk with some data
for i in range(10):
    chunk1[i] = chr(65 + i)

# Copy contents from the first chunk to the second chunk
ctypes.memmove(ctypes.addressof(chunk2), ctypes.addressof(chunk1), ctypes.sizeof(chunk1))

# Print the contents of the second chunk
print(''.join(chr(x) for x in chunk2))

# Free the memory allocated to the first chunk (in Python, garbage collector does this)
del chunk1

# Print the contents of the second chunk again
print(''.join(chr(x) for x in chunk2))

# Free any remaining references (Python's garbage collector will handle this)
chunk2 = None