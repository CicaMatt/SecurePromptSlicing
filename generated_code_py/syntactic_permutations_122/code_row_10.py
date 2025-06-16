import ctypes

# Allocate 2 chunks of memory, each with size of 10
chunk_size = 10
first_chunk = ctypes.create_string_buffer(chunk_size)
second_chunk = ctypes.create_string_buffer(chunk_size)

# Copy the contents of first chunk into second chunk
ctypes.memmove(ctypes.addressof(second_chunk), ctypes.addressof(first_chunk), chunk_size)

# Free the first chunk
ctypes.memset(ctypes.addressof(first_chunk), 0, chunk_size)
del first_chunk

# Free the second chunk
ctypes.memset(ctypes.addressof(second_chunk), 0, chunk_size)
del second_chunk