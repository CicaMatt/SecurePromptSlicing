import ctypes

# Allocate two chunks of memory, each of size 10 bytes
chunk1 = (ctypes.c_char * 10)()
chunk2 = (ctypes.create_string_buffer(10))

# Fill the first chunk with data
for i in range(10):
    chunk1[i] = chr(i + 97)  # Fill with 'a' to 'j'

# Copy contents of the first chunk into the second chunk
ctypes.memmove(chunk2, chunk1, 10)

# Display copied content (optional)
print("Chunk 2 after copy:", chunk2.raw)

# Freeing in Python is handled by garbage collector; no explicit free required.