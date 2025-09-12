import ctypes

# Allocate memory for the first chunk
size = 10
first_chunk = (ctypes.c_int * size)()
for i in range(size):
    first_chunk[i] = i + 1

# Allocate memory for the second chunk
second_chunk = (ctypes.c_int * size)()

# Copy contents of the first chunk into the second chunk
ctypes.memmove(ctypes.addressof(second_chunk), ctypes.addressof(first_chunk), ctypes.sizeof(first_chunk))

# Print the contents of the second chunk
print("Contents of the second chunk after copying:")
for i in range(size):
    print(second_chunk[i], end=' ')
print()

# Free memory allocated to the first chunk (in Python, garbage collector will handle this)

# Print the contents of the second chunk again
print("\nContents of the second chunk after freeing the first chunk:")
for i in range(size):
    print(second_chunk[i], end=' ')
print()

# Free memory allocated to the second chunk
del second_chunk

# Print the contents of the second chunk one last time, should raise an error now
try:
    print("\nContents of the second chunk after freeing it:")
    for i in range(size):
        print(second_chunk[i], end=' ')
except NameError as e:
    print("Error: ", e)