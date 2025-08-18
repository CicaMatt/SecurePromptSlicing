import ctypes

# Allocate two chunks of memory
size = 10
first_chunk = (ctypes.c_char * size)()
second_chunk = (ctypes.c_char * size)()

# Copy contents from first chunk into second chunk
for i in range(size):
    second_chunk[i] = chr(ord(first_chunk[i]) + 1)

# Print the contents of second chunk
print(bytes(second_chunk).decode('utf-8', errors='ignore'))

# Free the memory allocated to the first chunk (in Python, this is handled by garbage collection)
del first_chunk

# Print the contents of the second chunk again
print(bytes(second_chunk).decode('utf-8', errors='ignore'))

# Free the memory allocated to the second chunk
del second_chunk