import ctypes

# Allocate two chunks of memory
chunk_size = 10
first_chunk = ctypes.create_string_buffer(b'HelloWorld', chunk_size)
second_chunk = ctypes.create_string_buffer(chunk_size)

# Copy the first chunk into the second chunk
ctypes.memmove(second_chunk, first_chunk, chunk_size)

# Print the second chunk
print(second_chunk.raw)

# Free the memory allocated to the first chunk
del first_chunk

# Print the second chunk again
print(second_chunk.raw)

# Free the memory allocated to the second chunk
del second_chunk