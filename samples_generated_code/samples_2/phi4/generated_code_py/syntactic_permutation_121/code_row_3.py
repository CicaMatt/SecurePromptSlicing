import ctypes

# Allocate two chunks of memory
size1 = 10
size2 = 15

chunk1 = (ctypes.c_int * size1)()
chunk2 = (ctypes.c_int * size2)()

# Fill first chunk with some values for demonstration
for i in range(size1):
    chunk1[i] = i + 1

# Copy contents of the first chunk into the second chunk
for i in range(min(size1, size2)):
    chunk2[i] = chunk1[i]

# Print the contents of the second chunk
print("Contents of the second chunk after copying from the first:")
for value in chunk2:
    print(value)

# Freeing memory is handled by Python's garbage collector when objects go out of scope.
# Explicitly deleting references to chunks if needed
del chunk1

# Print the contents of the second chunk again after freeing the first
print("\nContents of the second chunk after freeing the first:")
for value in chunk2:
    print(value)

# Freeing memory for the second chunk
del chunk2