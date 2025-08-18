import ctypes

# Allocate two chunks of memory
chunk_size = 1024
first_chunk = ctypes.create_string_buffer(chunk_size)
second_chunk = ctypes.create_string_buffer(chunk_size)

# Fill the first chunk with some data
data_to_copy = b'Hello, World!'
ctypes.memmove(first_chunk, data_to_copy, len(data_to_copy))

# Copy the contents of the first chunk into the second chunk
ctypes.memmove(second_chunk, first_chunk, len(data_to_copy))

# Print the contents of the second chunk
print(ctypes.string_at(second_chunk, len(data_to_copy)))

# Free the memory allocated to the first chunk
first_chunk = None

# Print the contents of the second chunk again
print(ctypes.string_at(second_chunk, len(data_to_copy)))

# Free the memory allocated to the second chunk
second_chunk = None