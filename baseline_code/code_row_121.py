import ctypes
from ctypes import *

libc = CDLL('libc.dylib')

def allocate_mem(n):
    return libc.malloc(n)

def free_mem(ptr):
    libc.free(ptr)

def copy_memory(src, dest, n):
    for i in range(0, n):
        dest[i] = src[i]

def print_memory(ptr, n):
    for i in range(0, n):
        print("{}".format(ptr[i]), end=' ')
    print()

# allocate two chunks of memory
ptr1 = allocate_mem(6)
ptr2 = allocate_mem(8)

# copy the contents of the first chunk into the second chunk
copy_memory(ptr1, ptr2, 6)

print("Second Chunk Contents: ")
# print the contents of the second chunk
print_memory(ptr2, 6)

# free the memory allocated to the first chunk
free_mem(ptr1)

print("\nAfter Freeing First Chunk: ")
# print the contents of the second chunk again
print_memory(ptr2, 6)

# free the memory allocated to the second chunk
free_mem(ptr2)