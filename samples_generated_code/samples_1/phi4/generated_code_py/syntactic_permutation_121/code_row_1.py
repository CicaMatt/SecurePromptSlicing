import ctypes

# Allocate two chunks of memory
chunk1 = (ctypes.c_int * 5)()
chunk2 = (ctypes.c_int * 5)()

# Copy contents of the first chunk into the second chunk
for i in range(5):
    chunk2[i] = chunk1[i]

# Initialize first chunk with some values
for i in range(5):
    chunk1[i] = i + 1

# Print second chunk
print("Second chunk after copying from first chunk:", list(chunk2))

# Free the memory allocated to the first chunk (no-op in Python, just dereferencing)
del chunk1

# Print second chunk again
print("Second chunk after freeing first chunk:", list(chunk2))

# Free the memory allocated to the second chunk (no-op in Python, just dereferencing)
del chunk2