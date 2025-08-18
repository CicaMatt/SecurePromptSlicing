import ctypes

# Allocate memory for the first chunk
first_chunk = ctypes.create_string_buffer(10)

# Allocate memory for the second chunk
second_chunk = ctypes.create_string_buffer(10)

# Example data to copy into the first chunk
data_to_copy = b'abcdefghij'
ctypes.memmove(first_chunk, data_to_copy, 10)

# Copy contents of the first chunk into the second chunk
ctypes.memmove(second_chunk, first_chunk, 10)

# Free the first chunk (in CPython, memory is managed by the garbage collector)
del first_chunk

# Free the second chunk (in CPython, memory is managed by the garbage collector)
del second_chunk