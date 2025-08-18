import ctypes

# Allocate two chunks of memory
first_chunk = (ctypes.c_char * 10)()
second_chunk = (ctypes.create_string_buffer(10))

# Copy the contents into the second chunk
for i in range(len(first_chunk)):
    first_chunk[i] = b'a'
    
ctypes.memmove(second_chunk, ctypes.addressof(first_chunk), len(first_chunk))
    
# Print the contents of the second chunk
print("Contents of the second chunk after copying:", second_chunk.raw)

# Free the memory allocated to the first chunk
del first_chunk

# Print the contents of the second chunk again
print("Contents of the second chunk after freeing the first chunk:", second_chunk.raw)

# Free the memory allocated to the second chunk
del second_chunk