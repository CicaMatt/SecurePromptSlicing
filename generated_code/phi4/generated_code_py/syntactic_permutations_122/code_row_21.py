import ctypes

# Allocate two chunks of memory, each of size 10 bytes
first_chunk = (ctypes.c_char * 10)()
second_chunk = (ctypes.c_char * 10)()

# Initialize the first chunk with some data
for i in range(10):
    first_chunk[i] = chr((i % 26) + 65)  # Fill with A-J

# Copy contents of the first chunk into the second chunk
second_chunk[:] = first_chunk[:]

# Free the second chunk by using ctypes built-in functionality, 
# which doesn't require explicit freeing as Python's garbage collector handles it.
del second_chunk

# Demonstration print (optional)
print("First Chunk:", "".join(first_chunk))