import ctypes

# Allocate two chunks of memory
first_chunk = ctypes.create_string_buffer(b"Hello, World!", 13)
second_chunk = ctypes.create_string_buffer(13)

# Copy the contents of the first chunk into the second chunk
ctypes.memmove(second_chunk, first_chunk, 13)

# Print the contents of the second chunk
print(second_chunk.raw[:13].decode())

# Free the memory allocated to the first chunk
first_chunk = None

# Print the contents of the second chunk
print(second_chunk.raw[:13].decode())

# Free the memory allocated to the second chunk
second_chunk = None