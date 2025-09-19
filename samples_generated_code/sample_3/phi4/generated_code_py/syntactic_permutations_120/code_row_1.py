import ctypes

# Allocate first chunk of memory (8 bytes)
chunk1_size = 8
first_chunk = (ctypes.c_char * chunk1_size)()

# Fill the first chunk with some data
for i in range(chunk1_size):
    first_chunk[i] = bytes([i % 256])

# Allocate second chunk of memory (same size as the first)
second_chunk = (ctypes.c_char * chunk1_size)()

# Copy contents from first to second chunk
for i in range(chunk1_size):
    second_chunk[i] = first_chunk[i]

# Print the contents of the second chunk
print("Contents of the second chunk:")
for byte in second_chunk:
    print(byte, end=' ')