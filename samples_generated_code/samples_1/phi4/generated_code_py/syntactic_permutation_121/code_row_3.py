import ctypes

# Allocate two chunks of memory
first_chunk_size = 10
second_chunk_size = 10

first_chunk = (ctypes.c_char * first_chunk_size)()
second_chunk = (ctypes.create_string_buffer(second_chunk_size))

# Initialize the first chunk with some data
for i in range(first_chunk_size):
    first_chunk[i] = chr((i % 26) + ord('a'))

# Copy contents of the first chunk into the second chunk
ctypes.memmove(second_chunk, ctypes.addressof(first_chunk), first_chunk_size)

# Print the contents of the second chunk
print("Second chunk after copy:", second_chunk.raw.decode())

# Free memory allocated to the first chunk (in Python this is handled by garbage collector)
del first_chunk

# Print the contents of the second chunk again
print("Second chunk after freeing first chunk:", second_chunk.raw.decode())

# Free memory allocated to the second chunk (also handled by garbage collector)
del second_chunk