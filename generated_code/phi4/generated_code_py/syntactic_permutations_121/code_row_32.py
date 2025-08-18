import ctypes

# Allocate two chunks of memory
chunk1 = (ctypes.c_char * 10)()
chunk2 = (ctypes.c_char * 10)()

# Copy contents from the first chunk to the second chunk
for i in range(10):
    chunk2[i] = chr(ord('a') + i)

# Print the contents of the second chunk
print("Contents of the second chunk after copying:")
for char in chunk2:
    print(char.decode(), end=' ')
print()

# Free the memory allocated to the first chunk (in Python, this is automatic garbage collection)
del chunk1

# Print the contents of the second chunk again
print("\nContents of the second chunk after freeing the first chunk:")
for char in chunk2:
    print(char.decode(), end=' ')

# Explicitly free the second chunk by deleting it
del chunk2