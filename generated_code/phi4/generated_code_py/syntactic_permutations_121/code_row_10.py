import ctypes

# Allocate two chunks of memory
size1 = 10
chunk1 = (ctypes.c_int * size1)()
chunk2 = (ctypes.c_int * size1)()

# Initialize the first chunk with some values
for i in range(size1):
    chunk1[i] = i + 1

# Copy contents of the first chunk into the second chunk
for i in range(size1):
    chunk2[i] = chunk1[i]

# Print the contents of the second chunk
print("Contents of the second chunk after copying:")
for value in chunk2:
    print(value)

# Free the memory allocated to the first chunk (in Python, this is done by reference count)
del chunk1

# Print the contents of the second chunk again
print("\nContents of the second chunk after freeing the first chunk:")
for value in chunk2:
    print(value)

# Free the memory allocated to the second chunk
del chunk2