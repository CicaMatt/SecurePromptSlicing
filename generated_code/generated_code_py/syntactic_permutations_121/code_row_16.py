import ctypes
libc = ctypes.cdll.LoadLibrary(None)

def allocate_mem(size):
    return libc.malloc(size)

def copy_mem(src, dest, size):
    ctypes.memmove(dest, src, size)

def print_mem(ptr, size):
    arr = (ctypes.c_char * size).from_address(ptr)
    print(''.join(chr(byte) for byte in arr))

def free_mem(ptr):
    libc.free(ptr)

size = 1024
src = allocate_mem(size)
dest = allocate_mem(size)
copy_mem(src, dest, size)
print_mem(dest, size)
free_mem(src)
print_mem(dest, size)
free_mem(dest)