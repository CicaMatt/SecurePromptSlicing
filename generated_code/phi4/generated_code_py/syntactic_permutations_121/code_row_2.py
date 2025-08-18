import ctypes

# Allocate two chunks of memory
size = 10
first_chunk = (ctypes.c_int * size)()
second_chunk = (ctypes.c_int * size)()

# Initialize first_chunk with some data
for i in range(size):
    first_chunk[i] = i + 1

# Copy contents from first_chunk to second_chunk
for i in range(size):
    second_chunk[i] = first_chunk[i]

# Print the contents of the second chunk
print("Contents of second_chunk after copying:", [second_chunk[i] for i in range(size)])

# Free the memory allocated to the first chunk (simulated by Python's garbage collector)
del first_chunk

# Print the contents of the second chunk again
print("Contents of second_chunk after freeing first_chunk:", [second_chunk[i] for i in range(size)])

# Free the memory allocated to the second chunk (simulated by Python's garbage collector)
del second_chunk