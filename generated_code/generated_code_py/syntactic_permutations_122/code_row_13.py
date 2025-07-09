import ctypes
import os
from mmap import mmap, MAP_PRIVATE, MAP_ANONYMOUS

def main():
    ptr1 = ctypes.c_void_p()
    ptr2 = ctypes.c_void_p()
    try:
        size = 10 * os.sysconf('SC_PAGESIZE')
        ptr1.value = mmap(ctypes.c_void_p(), size, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0)
        ptr2.value = mmap(ctypes.c_void_p(), size, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0)
    except:
        print("Memory allocation failed!")
    else:
        ctypes.memmove(ptr2.value, ptr1.value, size)
    finally:
        if munmap(ptr1.value, size) == -1:
            print("Unable to free memory!")
        if munmap(ptr2.value, size) == -1:
            print("Unable to free memory!")

main()