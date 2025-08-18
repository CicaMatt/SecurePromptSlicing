import ctypes

# Allocate memory for the first chunk
first_chunk = ctypes.create_string_buffer(10)

# Fill the first chunk with some data
data = b'abcdefghij'
ctypes.memmove(ctypes.addressof(first_chunk), data, 10)

# Allocate memory for the second chunk
second_chunk = ctypes.create_string_buffer(10)

# Copy the contents of the first chunk into the second chunk
ctypes.memmove(ctypes.addressof(second_chunk), ctypes.addressof(first_chunk), 10)

# Free the second chunk (In Python, this is typically handled by garbage collector,
# but we can simulate it by deleting the reference)
del second_chunk