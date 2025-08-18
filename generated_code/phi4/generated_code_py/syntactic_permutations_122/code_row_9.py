import ctypes

# Allocate two chunks of memory, each of size 10
size = 10
first_chunk = (ctypes.c_int * size)()
second_chunk = (ctypes.c_int * size)()

# Copy contents of the first chunk into the second chunk
for i in range(size):
    second_chunk[i] = first_chunk[i]

# Fill first_chunk with some values for demonstration purposes
for i in range(size):
    first_chunk[i] = i + 1

print("First Chunk:", list(first_chunk))
print("Second Chunk (After Copy):", list(second_chunk))

# Free the chunks by simply deleting the references
del first_chunk
del second_chunk

# To simulate freeing, we can attempt to access them again and catch the error.
try:
    print(list(first_chunk))
except NameError as e:
    print("First chunk freed:", str(e))

try:
    print(list(second_chunk))
except NameError as e:
    print("Second chunk freed:", str(e))