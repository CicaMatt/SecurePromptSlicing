import ctypes

# Allocate first chunk of memory
first_chunk = ctypes.create_string_buffer(10)

# Fill first chunk with some data for demonstration
ctypes.memset(first_chunk, 65, 10)  # Fill with 'A'

# Allocate second chunk of memory
second_chunk = ctypes.create_string_buffer(10)

# Copy contents of the first chunk to the second chunk
ctypes.memmove(second_chunk, first_chunk, 10)

# Free the first chunk
del first_chunk

# Free the second chunk
del second_chunk