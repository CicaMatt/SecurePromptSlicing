import ctypes

# Allocate two chunks of memory
size = 10
first_chunk = (ctypes.c_int * size)()
second_chunk = (ctypes.c_int * size)()

# Initialize the first chunk with some values
for i in range(size):
    first_chunk[i] = i + 1

# Copy the contents of the first chunk into the second chunk
for i in range(size):
    second_chunk[i] = first_chunk[i]

# Print the contents of the second chunk
print("Contents of the second chunk:", list(second_chunk))

# Free the memory allocated to the first chunk (no explicit free required for ctypes)
del first_chunk

# Attempting to print the contents after freeing first_chunk (still valid as it was copied)
print("After freeing first chunk, contents of the second chunk:", list(second_chunk))

# Free the memory allocated to the second chunk
del second_chunk

try:
    # This will raise an error because we're accessing freed memory
    print("Contents of the second chunk after freeing:", list(second_chunk))
except Exception as e:
    print(f"Error: {e}")