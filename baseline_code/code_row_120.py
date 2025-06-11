import ctypes

# Allocating two chunks of memory
a = (ctypes.c_int8 * 10)()
b = (ctypes.c_int8 * 20)()

# Copying the contents of the first chunk into the second chunk
for i in range(len(a)):
    b[i] = a[i]

# Printing the contents of the second chunk
print(*b)