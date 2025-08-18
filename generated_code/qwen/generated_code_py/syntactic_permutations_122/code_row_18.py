import ctypes

# Allocate two chunks of memory, each of size 10 bytes
memory_chunk1 = ctypes.create_string_buffer(10)
memory_chunk2 = ctypes.create_string_buffer(10)

# Copy contents of the first chunk to the second chunk
ctypes.memmove(memory_chunk2, memory_chunk1, 10)

# Free the first chunk (in CPython, memory is managed by Python's garbage collector,
# but we can simulate freeing by deleting the reference)
del memory_chunk1

# Free the second chunk
del memory_chunk2