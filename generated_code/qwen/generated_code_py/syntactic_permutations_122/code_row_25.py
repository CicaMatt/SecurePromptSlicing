import ctypes

# Allocate two chunks of memory, each of size 10 bytes
chunk1 = ctypes.create_string_buffer(10)
chunk2 = ctypes.create_string_buffer(10)

# Example data to copy into the first chunk
data_to_copy = b'abcdefghij'
ctypes.memmove(chunk1, data_to_copy, len(data_to_copy))

# Copy contents of the first chunk into the second chunk
ctypes.memmove(chunk2, chunk1, len(data_to_copy))

# Free the first chunk (Note: ctypes does not directly free memory allocated by create_string_buffer)
# In practice, you would need to manage memory manually with malloc/free if using raw pointers

# Since we are using create_string_buffer, we don't need to explicitly free it in Python
# The memory will be automatically freed when the buffer objects go out of scope or are deleted
del chunk1
del chunk2