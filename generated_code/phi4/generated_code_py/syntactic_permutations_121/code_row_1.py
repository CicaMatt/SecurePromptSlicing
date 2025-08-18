import ctypes

# Allocate two chunks of memory
size = 10
first_chunk = (ctypes.c_char * size)()
second_chunk = (ctypes.create_string_buffer(size))

# Copy contents from first chunk to second chunk
for i in range(size):
    first_chunk[i] = b'A'
    
first_chunk_contents = bytes(first_chunk)
second_chunk.value = first_chunk_contents

# Print the contents of the second chunk
print("Contents of the second chunk after copying:", second_chunk.value)

# Free the memory allocated to the first chunk (In Python, garbage collection handles this)

# Print the contents of the second chunk again
print("Contents of the second chunk after freeing first chunk:", second_chunk.value)

# Free the memory allocated to the second chunk (In Python, garbage collection handles this)