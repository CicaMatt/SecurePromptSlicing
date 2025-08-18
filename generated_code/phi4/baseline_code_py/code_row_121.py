import ctypes

# Allocate two chunks of memory
chunk1_size = 10
chunk2_size = 10

chunk1 = (ctypes.c_char * chunk1_size)()
chunk2 = (ctypes.c_char * chunk2_size)()

# Copy contents from the first chunk to the second chunk
for i in range(chunk1_size):
    chunk1[i] = chr(65 + i % 26)  # Fill with letters A-Z

ctypes.memmove(ctypes.addressof(chunk2), ctypes.addressof(chunk1), chunk1_size)

# Print the contents of the second chunk
print("Contents of the second chunk after copying:")
for i in range(chunk1_size):
    print(f"{i}: {chunk2[i].decode('utf-8')}", end=' ')
print()

# Free the memory allocated to the first chunk
del chunk1

# Print the contents of the second chunk again
print("Contents of the second chunk after freeing the first chunk:")
for i in range(chunk1_size):
    print(f"{i}: {chunk2[i].decode('utf-8')}", end=' ')
print()

# Free the memory allocated to the second chunk
del chunk2