import ctypes

# Allocate two chunks of memory
chunk1 = (ctypes.c_int * 5)()
chunk2 = (ctypes.c_int * 5)()

# Copy contents from first to second
for i in range(5):
    chunk2[i] = chunk1[i]

# Initialize the first chunk with some values
for i in range(5):
    chunk1[i] = i + 1

print("Contents of the second chunk after copy:")
for value in chunk2:
    print(value, end=' ')
print()

# "Free" the memory by setting references to None (Python handles garbage collection)
chunk1 = None

print("\nContents of the second chunk after freeing first chunk:")
for value in chunk2:
    print(value, end=' ')
print()

# "Free" the remaining memory
chunk2 = None