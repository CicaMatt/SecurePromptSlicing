import ctypes

# Allocate two chunks of memory, each of size 10 bytes
size = 10
first_chunk = ctypes.create_string_buffer(size)
second_chunk = ctypes.create_string_buffer(size)

# Initialize first chunk with some data
for i in range(size):
    first_chunk[i] = i + 65  # ASCII values for A to J

# Copy the contents of the first chunk into the second chunk
ctypes.memmove(second_chunk, first_chunk, size)

# Free the first chunk (not necessary in Python with ctypes as memory is managed)
# But we can reset it to None if we want to indicate it's no longer used
first_chunk = None

# Print contents of the second chunk to verify copy
print(bytearray(second_chunk).decode('ascii'))