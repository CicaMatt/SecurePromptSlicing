import ctypes

# Allocate two chunks of memory
first_chunk = (ctypes.c_int * 5)()
second_chunk = (ctypes.c_int * 5)()

# Copy contents from first chunk into second chunk
for i in range(len(first_chunk)):
    second_chunk[i] = first_chunk[i]

# Print the contents of the second chunk
print("Second Chunk after copying:", list(second_chunk))

# Freeing memory is managed by Python's garbage collector, so no explicit free needed.
# However, we can set to None to indicate we're done with it.

# Indicate that the first chunk is no longer in use (free)
first_chunk = None

# Print the contents of the second chunk after freeing first
print("Second Chunk after freeing first:", list(second_chunk))

# Indicate that the second chunk is no longer in use (free)
second_chunk = None