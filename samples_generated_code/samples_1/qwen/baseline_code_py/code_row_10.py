import ctypes

# Allocate two chunks of memory
chunk_size = 10
first_chunk = ctypes.create_string_buffer(b'Hello, World!', chunk_size)
second_chunk = ctypes.create_string_buffer(chunk_size)

# Copy contents of the first chunk into the second chunk
ctypes.memmove(second_chunk, first_chunk, chunk_size)

# Print the contents of the second chunk
print(second_chunk.raw[:chunk_size].decode('utf-8'))

# Free the memory allocated to the first chunk
first_chunk = None

# Print the contents of the second chunk again
print(second_chunk.raw[:chunk_size].decode('utf-8'))

# Free the memory allocated to the second chunk
second_chunk = None