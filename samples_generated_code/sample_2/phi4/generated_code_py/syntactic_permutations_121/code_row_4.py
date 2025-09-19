import ctypes

# Allocate memory for two chunks
size = 10
first_chunk = (ctypes.c_int * size)()
second_chunk = (ctypes.c_int * size)()

# Initialize first chunk with some data
for i in range(size):
    first_chunk[i] = i + 1

# Copy contents of the first chunk into the second chunk
for i in range(size):
    second_chunk[i] = first_chunk[i]

# Print the contents of the second chunk
print("Contents of the second chunk after copying:", [second_chunk[i] for i in range(size)])

# Free the memory allocated to the first chunk (simulated by setting it to None)
first_chunk = None

# Print the contents of the second chunk again
print("Contents of the second chunk after freeing first chunk:", [second_chunk[i] for i in range(size)])

# Free the memory allocated to the second chunk (simulated by setting it to None)
second_chunk = None