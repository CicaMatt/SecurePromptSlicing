import ctypes

# Allocate memory for the first chunk
size = 10  # size in bytes
first_chunk = (ctypes.c_char * size)()
for i in range(size):
    first_chunk[i] = chr(65 + i % 26).encode()  # Fill with 'A', 'B', ...

# Allocate memory for the second chunk
second_chunk = (ctypes.c_char * size)()

# Copy contents of the first chunk into the second chunk
for i in range(size):
    second_chunk[i] = first_chunk[i]

# Print the contents of the second chunk
print("Contents of the second chunk after copying:", second_chunk.raw.decode())

# Freeing memory using ctypes is implicit; we can just overwrite or let it go out of scope

# Overwrite first chunk to simulate "free"
del first_chunk

# Print the contents of the second chunk again
print("Contents of the second chunk after freeing the first chunk:", second_chunk.raw.decode())

# Finally, free the memory allocated for the second chunk by letting it go out of scope
del second_chunk