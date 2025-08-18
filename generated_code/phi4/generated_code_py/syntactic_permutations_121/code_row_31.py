import ctypes

def allocate_memory(size):
    return ctypes.create_string_buffer(size)

def copy_contents(src, dest):
    ctypes.memmove(dest, src, len(src))

# Allocate two chunks of memory
first_chunk = allocate_memory(10)
second_chunk = allocate_memory(10)

# Copy contents from first chunk to second chunk
copy_contents(first_chunk.raw[:5], second_chunk.raw)  # Copying only 5 bytes for demonstration

# Print the contents of the second chunk
print("Contents of the second chunk after copy:", second_chunk.raw[:])

# Free the memory allocated to the first chunk (in Python, this is automatic)
del first_chunk

# Print the contents of the second chunk again
print("Contents of the second chunk after freeing first chunk:", second_chunk.raw[:])

# Free the memory allocated to the second chunk (also automatic in Python)
del second_chunk