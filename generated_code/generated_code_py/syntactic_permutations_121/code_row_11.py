import ctypes

# Allocate two chunks of memory
first_chunk = ctypes.malloc(ctypes.c_int * 5)
second_chunk = ctypes.malloc(ctypes.c_int * 5)

# Copy into the second chunk
for i in range(5):
    second_chunk[i] = first_chunk[i]

# Print contents of second chunk
print("Second Chunk:")
for i in range(5):
    print(second_chunk[i])

# Free memory allocated to first chunk
ctypes.free(first_chunk)

# Print contents of second chunk
print("\nSecond Chunk:")
for i in range(5):
    print(second_chunk[i])

# Free memory allocated to second chunk
ctypes.free(second_chunk)