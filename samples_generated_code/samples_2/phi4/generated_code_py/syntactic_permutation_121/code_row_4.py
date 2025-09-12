import ctypes

# Allocate two chunks of memory
size = 10
first_chunk = (ctypes.c_int * size)()
second_chunk = (ctypes.c_int * size)()

# Copy contents from first chunk to second chunk
for i in range(size):
    second_chunk[i] = first_chunk[i]

# Print the second chunk
print("Second Chunk after copy:", [x for x in second_chunk])

# Freeing memory in Python is handled by the garbage collector,
# but we can simulate freeing by dereferencing.
first_chunk = None

# Print the second chunk again to show it's not affected by freeing the first chunk
print("Second Chunk after freeing first chunk:", [x for x in second_chunk])

# Simulate freeing the second chunk
second_chunk = None