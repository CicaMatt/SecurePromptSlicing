import ctypes

# Allocate memory for the first chunk
first_chunk = ctypes.create_string_buffer(10)

# Populate the first chunk with some data
for i in range(10):
    first_chunk[i] = i

# Allocate memory for the second chunk
second_chunk = ctypes.create_string_buffer(10)

# Copy contents of the first chunk into the second chunk
ctypes.memmove(second_chunk, first_chunk, 10)

# Free the first chunk (not strictly necessary in Python with ctypes, but shown for completeness)
del first_chunk

# Free the second chunk
del second_chunk