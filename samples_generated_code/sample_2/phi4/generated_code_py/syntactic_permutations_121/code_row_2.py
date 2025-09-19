import ctypes

# Allocate two chunks of memory
size = 10  # Example size
first_chunk = (ctypes.c_char * size)()
second_chunk = (ctypes.c_char * size)()

# Initialize first_chunk with some data
data = b"HelloWorld"
for i in range(size):
    if i < len(data):
        first_chunk[i] = data[i]
    else:
        first_chunk[i] = b' '[0]

# Copy contents of the first chunk into the second chunk
ctypes.memmove(second_chunk, first_chunk, size)

# Print the contents of the second chunk
print("Second chunk after copy:", bytes(second_chunk))

# Free the memory allocated to the first chunk (not necessary in Python as garbage collector handles it)
del first_chunk

# Print the contents of the second chunk again
print("Second chunk after freeing first chunk:", bytes(second_chunk))

# "Free" the second chunk by deleting its reference
del second_chunk

# In a real scenario, proper memory management would be required in languages like C/C++