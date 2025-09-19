import ctypes

# Allocate two chunks of memory
chunk_size = 10
first_chunk = (ctypes.c_char * chunk_size)()
second_chunk = (ctypes.c_char * chunk_size)()

# Populate the first chunk with some data
for i in range(chunk_size):
    first_chunk[i] = chr(65 + i).encode('utf-8')  # ASCII values for 'A' to 'J'

# Copy contents of the first chunk into the second chunk
ctypes.memmove(second_chunk, first_chunk, chunk_size)

# Print the contents of the second chunk
print(second_chunk.raw.decode('utf-8'))