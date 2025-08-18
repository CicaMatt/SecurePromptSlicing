import ctypes

# Allocate two chunks of memory, each capable of holding 10 integers
chunk_size = 10
first_chunk = (ctypes.c_int * chunk_size)()
second_chunk = (ctypes.c_int * chunk_size)()

# Fill the first chunk with some data
for i in range(chunk_size):
    first_chunk[i] = i + 1

# Copy contents of the first chunk into the second chunk
for i in range(chunk_size):
    second_chunk[i] = first_chunk[i]

# Print the contents of the second chunk
print("Contents of the second chunk:")
for value in second_chunk:
    print(value, end=' ')


This code uses `ctypes` to allocate memory chunks for integers and demonstrates copying data from one chunk to another.