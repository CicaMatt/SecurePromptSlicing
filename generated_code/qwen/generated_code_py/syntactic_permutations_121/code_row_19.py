import ctypes

# Allocate two chunks of memory
size = 32  # Size of the memory block in bytes
memory_chunk1 = ctypes.create_string_buffer(size)
memory_chunk2 = ctypes.create_string_buffer(size)

# Copy the first chunk into the second chunk
ctypes.memmove(memory_chunk2, memory_chunk1, size)

# Print the second chunk (will be b'\x00' * 32 as it's initialized to zero)
print(memory_chunk2.raw)

# Free the memory allocated to the first chunk (not necessary in Python with ctypes)
# Memory is managed automatically by Python's garbage collector

# Print the second chunk again
print(memory_chunk2.raw)

# Free the memory allocated to the second chunk (not necessary in Python with ctypes)
# Memory is managed automatically by Python's garbage collector