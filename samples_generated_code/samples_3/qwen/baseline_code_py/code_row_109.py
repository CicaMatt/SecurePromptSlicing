import ctypes

# Allocate memory for the first chunk
first_chunk = ctypes.create_string_buffer(10)

# Fill the first chunk with some data
for i in range(10):
    first_chunk[i] = i + 65  # ASCII values for 'A' to 'J'

# Allocate memory for the second chunk
second_chunk = ctypes.create_string_buffer(10)

# Copy contents from the first chunk to the second chunk
ctypes.memmove(second_chunk, first_chunk, 10)

# Free the first chunk (in CPython, this is automatic, but we can set it to None)
first_chunk = None

# Free the second chunk (in CPython, this is automatic, but we can set it to None)
second_chunk = None