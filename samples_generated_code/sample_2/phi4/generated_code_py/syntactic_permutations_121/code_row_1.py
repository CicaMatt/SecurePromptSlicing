import ctypes

# Allocate two chunks of memory
chunk1 = (ctypes.c_int * 10)()
chunk2 = (ctypes.c_int * 10)()

# Copy contents of first chunk into the second chunk
for i in range(len(chunk1)):
    chunk2[i] = chunk1[i]

# Print the second chunk before freeing the first chunk
print("Second chunk after copying from first chunk:", list(chunk2))

# Freeing memory for a ctypes array does not require explicit deallocation,
# Python's garbage collector will handle it. However, you can explicitly delete references.
del chunk1

# Print the second chunk after deleting the first chunk
print("Second chunk after freeing the first chunk:", list(chunk2))

# Explicitly delete reference to second chunk to free memory
del chunk2