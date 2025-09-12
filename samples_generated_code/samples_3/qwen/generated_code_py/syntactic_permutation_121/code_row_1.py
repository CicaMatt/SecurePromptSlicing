import ctypes

# Allocate two chunks of memory
size = 16  # Size in bytes
memory_chunk1 = ctypes.create_string_buffer(size)
memory_chunk2 = ctypes.create_string_buffer(size)

# Fill the first memory chunk with some data
data = b"Hello, World!"
ctypes.memmove(ctypes.addressof(memory_chunk1), data, len(data))

# Copy the contents of the first chunk into the second chunk
ctypes.memmove(ctypes.addressof(memory_chunk2), ctypes.addressof(memory_chunk1), size)

# Print the contents of the second chunk
print(memory_chunk2.raw[:len(data)].decode())

# Free the memory allocated to the first chunk (not necessary in Python, but simulating)
memory_chunk1 = None

# Print the contents of the second chunk again
print(memory_chunk2.raw[:len(data)].decode())

# Free the memory allocated to the second chunk (not necessary in Python, but simulating)
memory_chunk2 = None