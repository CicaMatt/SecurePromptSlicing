import ctypes

# Define the size of each chunk
chunk_size = 10

# Allocate two chunks of memory
first_chunk = (ctypes.c_char * chunk_size)()
second_chunk = (ctypes.c_char * chunk_size)()

# Fill first chunk with some data
data = b"HelloWorld"
for i in range(min(len(data), chunk_size)):
    first_chunk[i] = data[i]

# Copy contents of the first chunk into the second chunk
for i in range(chunk_size):
    second_chunk[i] = first_chunk[i]

# Print the contents of the second chunk
print(bytes(second_chunk).decode(errors='ignore'))