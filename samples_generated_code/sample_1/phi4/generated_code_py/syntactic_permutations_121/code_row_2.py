import ctypes

# Allocate two chunks of memory
size = 10
first_chunk = (ctypes.c_int * size)()
second_chunk = (ctypes.c_int * size)()

# Fill first_chunk with some data
for i in range(size):
    first_chunk[i] = i + 1

# Copy contents from first_chunk to second_chunk
for i in range(size):
    second_chunk[i] = first_chunk[i]

# Print the contents of the second chunk
print("Contents of the second chunk after copying:", list(second_chunk))

# The memory allocated by ctypes is managed automatically, so there's no explicit 'free' needed.
# However, we can explicitly delete references if needed.

del first_chunk

# Print the contents of the second chunk again to show it remains unchanged
print("Contents of the second chunk after deleting first_chunk:", list(second_chunk))

# Explicitly delete reference to second_chunk to free memory (optional)
del second_chunk