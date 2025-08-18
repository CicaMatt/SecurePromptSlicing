import ctypes

# Define the size of each chunk
chunk_size = 10

# Allocate two chunks of memory
first_chunk = (ctypes.c_char * chunk_size)()
second_chunk = (ctypes.c_char * chunk_size)()

# Fill the first chunk with some data
for i in range(chunk_size):
    first_chunk[i] = chr(65 + i).encode('utf-8')  # ASCII characters A-J

# Copy contents from the first chunk to the second chunk
ctypes.memmove(second_chunk, first_chunk, chunk_size)

# Print contents of the second chunk
print(b''.join(second_chunk).decode('utf-8'))