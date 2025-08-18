import ctypes

# Allocate two chunks of memory
size = 10
first_chunk = (ctypes.c_int * size)()
second_chunk = (ctypes.c_int * size)()

# Copy contents from the first chunk to the second chunk
for i in range(size):
    first_chunk[i] = i + 1  # Fill first_chunk with some values for demonstration

ctypes.memmove(second_chunk, ctypes.addressof(first_chunk), ctypes.sizeof(first_chunk))

# Print the contents of the second chunk
print("Contents of the second chunk:")
for value in second_chunk:
    print(value)