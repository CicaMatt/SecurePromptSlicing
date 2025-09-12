import ctypes

# Allocate two chunks of memory
size = 10
first_chunk = (ctypes.c_int * size)()
second_chunk = (ctypes.c_int * size)()

# Copy contents from first_chunk to second_chunk
for i in range(size):
    first_chunk[i] = i + 1
    second_chunk[i] = first_chunk[i]

# Print the contents of the second chunk
print("Contents of second chunk after copying:", [second_chunk[i] for i in range(size)])

# Free memory allocated to the first chunk (not needed explicitly in ctypes, but dereferencing)
first_chunk = None

# Print the contents of the second chunk again
print("Contents of second chunk after freeing first chunk:", [second_chunk[i] for i in range(size)])

# Free memory allocated to the second chunk
second_chunk = None