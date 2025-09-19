import ctypes

# Allocate two chunks of memory, each of size 10 bytes
first_chunk = (ctypes.c_char * 10)()
second_chunk = (ctypes.c_char * 10)()

# Fill the first chunk with some data
for i in range(10):
    first_chunk[i] = chr(i + 65).encode()  # A to J

# Copy contents of the first chunk into the second chunk
ctypes.memmove(second_chunk, first_chunk, 10)

# Print the contents of the second chunk for verification
print(bytes(second_chunk))

# Free memory (in Python, garbage collector handles this automatically)
del first_chunk
del second_chunk