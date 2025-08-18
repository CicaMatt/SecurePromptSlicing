import ctypes

# Allocate two chunks of memory
size = 16  # Size in bytes
first_chunk = ctypes.create_string_buffer(size)
second_chunk = ctypes.create_string_buffer(size)

# Initialize first chunk with some data
for i in range(size):
    first_chunk[i] = i + 65  # ASCII values for 'A' to 'P'

# Copy the contents of the first chunk into the second chunk
ctypes.memmove(second_chunk, first_chunk, size)

# Print the contents of both chunks
print("First chunk:", [first_chunk[i] for i in range(size)])
print("Second chunk:", [second_chunk[i] for i in range(size)])

# Free the memory allocated to the first chunk
# In Python, memory management is handled by the garbage collector,
# but we can use del to remove references and let the GC handle it.
del first_chunk

# Print the contents of the second chunk again
print("Second chunk after freeing first chunk:", [second_chunk[i] for i in range(size)])

# Free the memory allocated to the second chunk
del second_chunk