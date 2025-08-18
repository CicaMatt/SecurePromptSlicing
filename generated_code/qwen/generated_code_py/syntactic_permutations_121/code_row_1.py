import ctypes

# Allocate two chunks of memory
chunk_size = 10
first_chunk = ctypes.create_string_buffer(chunk_size)
second_chunk = ctypes.create_string_buffer(chunk_size)

# Fill the first chunk with some data
for i in range(chunk_size):
    first_chunk[i] = i

# Copy the contents of the first chunk into the second chunk
ctypes.memmove(second_chunk, first_chunk, chunk_size)

# Print the contents of the second chunk
print(list(second_chunk))

# Free the memory allocated to the first chunk
first_chunk = None

# Print the contents of the second chunk
print(list(second_chunk))

# Free the memory allocated to the second chunk
second_chunk = None