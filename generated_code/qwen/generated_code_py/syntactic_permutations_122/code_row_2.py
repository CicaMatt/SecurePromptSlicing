import ctypes

# Allocate memory for the first chunk
first_chunk = ctypes.create_string_buffer(10)

# Allocate memory for the second chunk
second_chunk = ctypes.create_string_buffer(10)

# Fill the first chunk with some data
for i in range(10):
    first_chunk[i] = i

# Copy contents of the first chunk into the second chunk
ctypes.memmove(second_chunk, first_chunk, 10)

# Free the first chunk (in Python, memory management is handled automatically,
# but we can simulate freeing by deleting the reference)
del first_chunk

# Free the second chunk
del second_chunk