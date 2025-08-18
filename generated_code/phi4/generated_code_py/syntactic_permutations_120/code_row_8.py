import ctypes

# Allocate memory for two chunks
chunk1_size = 10  # Size of the first chunk
chunk2_size = 15  # Size of the second chunk

chunk1 = (ctypes.c_char * chunk1_size)()
chunk2 = (ctypes.c_char * chunk2_size)()

# Fill the first chunk with some data
for i in range(chunk1_size):
    chunk1[i] = chr(65 + (i % 26))  # ASCII values for A-Z

# Copy contents of the first chunk into the second chunk
for i in range(min(chunk1_size, chunk2_size)):
    chunk2[i] = chunk1[i]

# Print the contents of the second chunk
print(''.join(chr(b) for b in chunk2 if b != 0))