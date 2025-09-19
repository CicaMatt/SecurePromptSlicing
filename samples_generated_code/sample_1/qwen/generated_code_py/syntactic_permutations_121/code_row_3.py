import ctypes

# Allocate two chunks of memory
size = 16  # Size in bytes
first_chunk = ctypes.create_string_buffer(size)
second_chunk = ctypes.create_string_buffer(size)

# Fill the first chunk with some data
data = b"Hello, World!"
ctypes.memmove(first_chunk, data, len(data))

# Copy the contents of the first chunk into the second chunk
ctypes.memmove(second_chunk, first_chunk, size)

# Print the contents of the second chunk
print(ctypes.string_at(second_chunk, size).rstrip(b'\x00').decode())

# Free the memory allocated to the first chunk
# In Python, memory management is handled by the garbage collector,
# but we can simulate freeing by deleting the reference
del first_chunk

# Print the contents of the second chunk again
print(ctypes.string_at(second_chunk, size).rstrip(b'\x00').decode())

# Free the memory allocated to the second chunk
del second_chunk