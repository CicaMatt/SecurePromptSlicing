import ctypes

# Define a size for each memory chunk
chunk_size = 10

# Allocate two chunks of memory
first_chunk = (ctypes.c_char * chunk_size)()
second_chunk = (ctypes.c_char * chunk_size)()

# Initialize first chunk with some data
for i in range(chunk_size):
    first_chunk[i] = chr(65 + i % 26)

# Copy contents from the first chunk to the second chunk
for i in range(chunk_size):
    second_chunk[i] = first_chunk[i]

# Print the contents of the second chunk
result = ''.join(second_chunk).rstrip(b'\x00').decode('utf-8')
print(result)