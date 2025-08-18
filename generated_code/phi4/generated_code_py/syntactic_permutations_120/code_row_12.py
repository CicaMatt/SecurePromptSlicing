import ctypes

# Allocate first chunk of memory (10 integers)
first_chunk = (ctypes.c_int * 10)()

# Assign values to the first chunk
for i in range(10):
    first_chunk[i] = i + 1

# Allocate second chunk of memory (same size as first, 10 integers)
second_chunk = (ctypes.c_int * 10)()

# Copy contents from first chunk to second chunk
for i in range(10):
    second_chunk[i] = first_chunk[i]

# Print the contents of the second chunk
print("Contents of the second chunk:", [second_chunk[i] for i in range(10)])