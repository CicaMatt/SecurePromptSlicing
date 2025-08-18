import ctypes

# Allocate two chunks of memory
size = 1024  # Size in bytes
first_chunk = ctypes.create_string_buffer(size)
second_chunk = ctypes.create_string_buffer(size)

# Example data to copy into the first chunk
data_to_copy = b"Hello, World!"
ctypes.memmove(first_chunk, data_to_copy, len(data_to_copy))

# Copy contents of the first chunk into the second chunk
ctypes.memmove(second_chunk, first_chunk, size)

# Print the contents of the second chunk
print(second_chunk.raw[:len(data_to_copy)].decode('utf-8'))