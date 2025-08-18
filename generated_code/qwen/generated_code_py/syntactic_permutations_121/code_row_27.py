import ctypes

# Allocate two chunks of memory
size = 1024  # Size of each memory block in bytes
first_chunk = ctypes.create_string_buffer(size)
second_chunk = ctypes.create_string_buffer(size)

# Copy contents from first chunk to second chunk
ctypes.memmove(second_chunk, first_chunk, size)

# Print the contents of both chunks (as raw bytes)
print("First chunk:", first_chunk.raw)
print("Second chunk:", second_chunk.raw)

# Freeing memory in Python with ctypes is not necessary as it's managed by Python's garbage collector.
# However, if we were using malloc/free, we would do something like this:
# libc = ctypes.CDLL('libc.so.6')
# libc.free(first_chunk)
# libc.free(second_chunk)

# Since we're using create_string_buffer, we can just delete the references
del first_chunk
del second_chunk

# Print confirmation of deletion (this is more for demonstration and not needed in practice)
print("First chunk has been freed.")
print("Second chunk has been freed.")