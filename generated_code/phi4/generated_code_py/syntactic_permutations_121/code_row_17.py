import ctypes

# Function to allocate a block of memory
def allocate_memory(size):
    return (ctypes.c_char * size)()

# Allocate two chunks of memory
size1 = 10
chunk1 = allocate_memory(size1)

# Initialize the first chunk with some data
for i in range(size1):
    chunk1[i] = chr(65 + i % 26).encode('utf-8')

# Copy contents from the first chunk to the second chunk
size2 = size1
chunk2 = allocate_memory(size2)
ctypes.memmove(ctypes.addressof(chunk2), ctypes.addressof(chunk1), size1)

# Print the contents of the second chunk
print("Contents of the second chunk after copying:", bytes(chunk2).decode('utf-8'))

# Free the first chunk (not applicable in Python, but demonstrate intention)
chunk1 = None

# Print the contents of the second chunk again
print("Contents of the second chunk after freeing the first chunk:", bytes(chunk2).decode('utf-8'))

# Free the second chunk
chunk2 = None