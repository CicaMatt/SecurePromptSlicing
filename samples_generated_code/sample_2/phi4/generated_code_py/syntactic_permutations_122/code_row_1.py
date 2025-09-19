import ctypes

# Define size of each memory chunk
chunk_size = 100

# Allocate two chunks of memory
first_chunk = (ctypes.c_char * chunk_size)()
second_chunk = (ctypes.c_char * chunk_size)()

# Initialize first chunk with some data
for i in range(chunk_size):
    first_chunk[i] = ctypes.c_char(chr(65 + (i % 26)))  # Fill with A-Z characters

# Copy contents of the first chunk into the second chunk
for i in range(chunk_size):
    second_chunk[i] = first_chunk[i]

# Free memory is not applicable in Python as it uses garbage collection.
# However, we can simulate by setting references to None
first_chunk = None
second_chunk = None

# In a real C or C++ environment, you would use free() or delete[] here,
# but in Python, this is managed automatically.

# Just for demonstration of access after "freeing"
if second_chunk:
    print("Second chunk contains:", ''.join(ctypes.string_at(ctypes.addressof(second_chunk), chunk_size)))
else:
    print("Both chunks are 'freed'")