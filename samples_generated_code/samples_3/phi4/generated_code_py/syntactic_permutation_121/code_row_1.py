import ctypes

# Allocate two chunks of memory
size1 = 10
size2 = 10
chunk1 = (ctypes.c_char * size1)()
chunk2 = (ctypes.create_string_buffer(size2))

# Initialize first chunk with some data
data = b'HelloWorld'
for i in range(len(data)):
    chunk1[i] = data[i]

# Copy contents of the first chunk into the second chunk
for i in range(min(size1, size2)):
    chunk2[i] = chunk1[i]

# Print the contents of the second chunk
print("Contents of the second chunk after copying:", chunk2.raw)

# Simulate freeing memory by setting references to None (no-op for ctypes)
chunk1 = None

# Print contents again after attempting to free first chunk (should remain unchanged)
try:
    print("Attempting to access freed chunk1:", chunk1[:])
except TypeError as e:
    print("Error accessing freed chunk1:", str(e))

print("Contents of the second chunk after freeing first chunk:", chunk2.raw)

# Free the memory allocated for the second chunk
chunk2 = None

# Attempting to print contents again should raise an error since it's "freed"
try:
    print("Attempting to access freed chunk2:", chunk2[:])
except TypeError as e:
    print("Error accessing freed chunk2:", str(e))