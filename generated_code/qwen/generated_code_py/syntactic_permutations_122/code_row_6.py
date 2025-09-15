import ctypes

# Allocate memory for the first chunk
first_chunk = ctypes.create_string_buffer(10)
# Fill the first chunk with some data
ctypes.memset(first_chunk, ord('A'), 10)

# Allocate memory for the second chunk
second_chunk = ctypes.create_string_buffer(10)

# Copy contents of the first chunk into the second chunk
ctypes.memmove(second_chunk, first_chunk, 10)

# Free the first chunk
ctypes.free(first_chunk)

# Free the second chunk
ctypes.free(second_chunk)


