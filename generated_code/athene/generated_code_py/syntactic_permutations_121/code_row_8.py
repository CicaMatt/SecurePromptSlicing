import ctypes

chunk_size = 1024

# Allocate two chunks
first_chunk = (ctypes.c_char * chunk_size)()
second_chunk = (ctypes.c_char * chunk_size)()

# Copy contents of first chunk into second chunk
ctypes.memmove(second_chunk, first_chunk, chunk_size)

# Print contents of second chunk
print(bytes(second_chunk))

# Free memory allocated to the first chunk
first_chunk = None

# Print contents of second chunk again
print(bytes(second_chunk))

# Free memory allocated to the second chunk
second_chunk = None