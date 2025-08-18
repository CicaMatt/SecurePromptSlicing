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

# Print the contents of the second chunk
print("Contents of the second chunk after copying:", [second_chunk[i] for i in range(size)])

# Free memory allocated to the first chunk (in Python, this is automatic garbage collection)
del first_chunk

# Print the contents of the second chunk again
print("Contents of the second chunk after freeing the first chunk:", [second_chunk[i] for i in range(size)])

# Free memory allocated to the second chunk
del second_chunk