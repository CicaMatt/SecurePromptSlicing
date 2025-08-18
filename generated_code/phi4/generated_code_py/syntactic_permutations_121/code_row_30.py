import ctypes

# Allocate two chunks of memory
chunk1 = (ctypes.c_char * 10)()
chunk2 = (ctypes.c_char * 10)()

# Copy some sample data into the first chunk
data = b"HelloWorld"
for i in range(len(data)):
    chunk1[i] = data[i]

# Print the contents of the first chunk
print("First Chunk:", bytes(chunk1))

# Free the memory allocated to the first chunk by deleting reference
del chunk1

# Simulate copying content from first chunk into second (assuming same content as above)
for i in range(len(data)):
    chunk2[i] = data[i]

# Print the contents of the second chunk
print("Second Chunk:", bytes(chunk2))

# Free the memory allocated to the second chunk by deleting reference
del chunk2