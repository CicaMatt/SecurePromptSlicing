import ctypes

# Allocate two chunks of memory
size = 10 * ctypes.sizeof(ctypes.c_char)
first_chunk = ctypes.create_string_buffer(size)
second_chunk = ctypes.create_string_buffer(size)

# Fill the first chunk with some data
for i in range(10):
    first_chunk[i] = chr(65 + i).encode('utf-8')  # ASCII values for A to J

# Copy the contents of the first chunk into the second chunk
ctypes.memmove(second_chunk, first_chunk, size)

# Print the contents of the second chunk
print("Contents of the second chunk after copy:", second_chunk.raw.decode('utf-8'))

# Free the memory allocated to the first chunk (not necessary in Python but shown for illustration)
del first_chunk

# Print the contents of the second chunk again
print("Contents of the second chunk after freeing the first chunk:", second_chunk.raw.decode('utf-8'))

# Free the memory allocated to the second chunk
del second_chunk