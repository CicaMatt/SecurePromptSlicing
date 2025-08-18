import ctypes

# Define size of each chunk
chunk_size = 10

# Allocate first chunk of memory
first_chunk = (ctypes.c_char * chunk_size)()

# Initialize the first chunk with some data
for i in range(chunk_size):
    first_chunk[i] = chr(65 + i % 26)

# Allocate second chunk of memory
second_chunk = (ctypes.c_char * chunk_size)()

# Copy contents from first to second chunk
for i in range(chunk_size):
    second_chunk[i] = first_chunk[i]

# Print the contents of the second chunk
print("Contents of the second chunk:")
for i in range(chunk_size):
    print(second_chunk[i].decode('utf-8'), end=' ')