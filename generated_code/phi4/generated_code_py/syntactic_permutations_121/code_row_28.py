import ctypes

# Allocate two chunks of memory
chunk1 = (ctypes.c_char * 10)()
chunk2 = (ctypes.c_char * 10)()

# Fill the first chunk with some data
for i in range(10):
    chunk1[i] = chr(i + ord('A'))

# Copy the contents of the first chunk into the second chunk
for i in range(10):
    chunk2[i] = chunk1[i]

# Print the contents of the second chunk
print("Second chunk after copying:", ''.join(ctypes.string_at(addressof(chunk2), 10)))

# Free the memory allocated to the first chunk (no-op in Python, as memory is managed by garbage collector)
del chunk1

# Print the contents of the second chunk again
print("Second chunk after freeing first chunk:", ''.join(ctypes.string_at(addressof(chunk2), 10)))

# Free the memory allocated to the second chunk (again, no-op in Python)
del chunk2