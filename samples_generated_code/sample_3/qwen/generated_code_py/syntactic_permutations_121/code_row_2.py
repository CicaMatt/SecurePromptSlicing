import ctypes

# Allocate two chunks of memory
size = 16  # Size in bytes
first_chunk = ctypes.create_string_buffer(size)
second_chunk = ctypes.create_string_buffer(size)

# Initialize the first chunk with some data
data = b"Hello, World!"
ctypes.memmove(first_chunk, data, len(data))

# Copy the contents of the first chunk into the second chunk
ctypes.memmove(second_chunk, first_chunk, size)

# Print the contents of the second chunk
print(ctypes.string_at(second_chunk, size).decode())

# Free the memory allocated to the first chunk
# Note: In Python, manual memory management is not typically required as ctypes handles it.
# However, we can set the buffer to None to release the reference.
first_chunk = None

# Print the contents of the second chunk again
print(ctypes.string_at(second_chunk, size).decode())

# Free the memory allocated to the second chunk
second_chunk = None