import ctypes

# Allocate two chunks of memory
size1 = 10
size2 = 20
first_chunk = (ctypes.c_char * size1)()
second_chunk = (ctypes.c_char * size2)()

# Fill first chunk with data
for i in range(size1):
    first_chunk[i] = chr(65 + i % 26)

# Copy contents of the first chunk into the second chunk
for i in range(min(size1, size2)):
    second_chunk[i] = first_chunk[i]

# Print contents of the second chunk
print("Contents of the second chunk after copying from first:")
for i in range(size2):
    print(second_chunk[i], end=' ')
print()

# Free memory allocated to the first chunk by setting it to None
first_chunk = None

# Print contents of the second chunk again
print("\nContents of the second chunk after freeing the first chunk:")
for i in range(size2):
    print(second_chunk[i] if i < size1 else ' ', end=' ')
print()

# Free memory allocated to the second chunk by setting it to None
second_chunk = None