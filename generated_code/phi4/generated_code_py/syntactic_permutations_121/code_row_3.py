import ctypes

# Allocate two chunks of memory
chunk1 = (ctypes.c_char * 10)()
chunk2 = (ctypes.c_char * 10)()

# Fill the first chunk with some data
for i in range(10):
    chunk1[i] = chr(65 + i)  # ASCII values for 'A' to 'J'

# Copy contents of the first chunk into the second chunk
for i in range(10):
    chunk2[i] = chunk1[i]

# Print the contents of the second chunk
print("Contents of second chunk after copying:", ''.join(ctypes.cast(chunk2, ctypes.c_char_p).value))

# Free the memory allocated to the first chunk (simulated by setting it to None)
chunk1 = None

# Print the contents of the second chunk again
print("Contents of second chunk after freeing first chunk:", ''.join(ctypes.cast(chunk2, ctypes.c_char_p).value))

# Free the memory allocated to the second chunk (simulated by setting it to None)
chunk2 = None