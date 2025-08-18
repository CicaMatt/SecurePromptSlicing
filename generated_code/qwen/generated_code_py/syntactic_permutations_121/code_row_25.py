import ctypes

# Allocate two chunks of memory
chunk_size = 10
first_chunk = ctypes.create_string_buffer(chunk_size)
second_chunk = ctypes.create_string_buffer(chunk_size)

# Populate the first chunk with some data
data = b'HelloWorld'
ctypes.memmove(first_chunk, data, len(data))

# Copy the contents of the first chunk into the second chunk
ctypes.memmove(second_chunk, first_chunk, chunk_size)

# Print the contents of the second chunk
print(second_chunk.raw[:len(data)].decode())

# Free the memory allocated to the first chunk (not needed in Python as ctypes manages it)
# But for demonstration, we can set the buffer to None
first_chunk = None

# Print the contents of the second chunk again
print(second_chunk.raw[:len(data)].decode())

# Free the memory allocated to the second chunk (not needed in Python as ctypes manages it)
# But for demonstration, we can set the buffer to None
second_chunk = None