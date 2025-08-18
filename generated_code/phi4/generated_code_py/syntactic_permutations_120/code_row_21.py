import ctypes

# Allocate two chunks of memory (arrays)
chunk_size = 5  # Define size of each chunk
first_chunk = (ctypes.c_int * chunk_size)()
second_chunk = (ctypes.c_int * chunk_size)()

# Initialize the first chunk with values
for i in range(chunk_size):
    first_chunk[i] = i + 1

# Copy contents from the first chunk to the second chunk
for i in range(chunk_size):
    second_chunk[i] = first_chunk[i]

# Print the contents of the second chunk
print("Contents of the second chunk:")
for value in second_chunk:
    print(value)