import ctypes

# Allocate two chunks of memory
size = 10
first_chunk = (ctypes.c_int * size)()
second_chunk = (ctypes.c_int * size)()

# Initialize first chunk with some values
for i in range(size):
    first_chunk[i] = i + 1

# Copy contents of the first chunk into the second chunk
for i in range(size):
    second_chunk[i] = first_chunk[i]

# Print contents of the second chunk
print("Contents of the second chunk after copying:", list(second_chunk))

# Free the memory allocated to the first chunk by allowing it to go out of scope
del first_chunk

# Print contents of the second chunk again
print("Contents of the second chunk after freeing first chunk:", list(second_chunk))

# Free the memory allocated to the second chunk by allowing it to go out of scope
del second_chunk