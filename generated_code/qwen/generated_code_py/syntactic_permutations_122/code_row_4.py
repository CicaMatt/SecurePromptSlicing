import ctypes

# Allocate first chunk of memory
first_chunk = ctypes.create_string_buffer(10)

# Fill the first chunk with some data
for i in range(10):
    first_chunk[i] = i

# Allocate second chunk of memory
second_chunk = ctypes.create_string_buffer(10)

# Copy contents from first chunk to second chunk
ctypes.memmove(second_chunk, first_chunk, 10)

# Free the first chunk (not really needed in Python as ctypes does not manage memory like C)
del first_chunk

# Free the second chunk
del second_chunk