import ctypes

# Allocate two chunks of memory
size = 10
first_chunk = (ctypes.c_int * size)()
second_chunk = (ctypes.c_int * size)()

# Copy first chunk into second chunk
for i in range(size):
    second_chunk[i] = first_chunk[i]

# Print the second chunk
print("Second chunk after copying:", [second_chunk[i] for i in range(size)])

# Free memory allocated to the first chunk (Python garbage collector handles this, but shown explicitly)
first_chunk = None

# Print the second chunk again
print("Second chunk after freeing first chunk's memory:", [second_chunk[i] for i in range(size)])

# Free memory allocated to the second chunk
second_chunk = None