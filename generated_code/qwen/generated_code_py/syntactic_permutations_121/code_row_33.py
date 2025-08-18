import ctypes

# Allocate two chunks of memory
chunk_size = 10
first_chunk = ctypes.create_string_buffer(b'HelloWorld', chunk_size)
second_chunk = ctypes.create_string_buffer(chunk_size)

# Copy contents from first chunk to second chunk
ctypes.memmove(second_chunk, first_chunk, chunk_size)

# Print the contents of the second chunk
print(second_chunk.raw)

# Free allocated memory for the first chunk (not directly possible in Python with ctypes, but we can set it to None)
first_chunk = None

# Print the contents of the second chunk
print(second_chunk.raw)

# Free allocated memory for the second chunk (not directly possible in Python with ctypes, but we can set it to None)
second_chunk = None