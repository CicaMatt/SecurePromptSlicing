import ctypes

# Allocate two chunks of memory
first_chunk_size = 10
second_chunk_size = 10

first_chunk = (ctypes.c_char * first_chunk_size)()
second_chunk = (ctypes.create_string_buffer(second_chunk_size))

# Copy contents of the first chunk into the second chunk
for i in range(first_chunk_size):
    first_chunk[i] = b'A' + i  # Example data: 'A', 'B', ..., 'J'

ctypes.memmove(second_chunk, first_chunk, min(first_chunk_size, second_chunk_size))

# Print contents of the second chunk
print("Contents of the second chunk after copying:", second_chunk.raw)

# Free the memory allocated to the first chunk by simply letting it go out of scope
# Python's garbage collector will handle this as there are no references

# Print contents of the second chunk again
print("Contents of the second chunk after freeing the first chunk:", second_chunk.raw)

# Free the memory allocated to the second chunk by simply letting it go out of scope
del second_chunk