python
import ctypes
from ctypes import *
libc = ctypes.CDLL(None)
libc.malloc.argtypes = ctypes.c_size_t,  # size of allocation
libc.malloc.restype = ctypes.POINTER(ctypes.c_void_p)  # pointer to allocated memory
def read1024(buf):
    return libc.read(0, buf, 1024)
def main():
    buf = libc.malloc(1024)  # allocate 1024 bytes for buffer
    buf1 = libc.malloc(1024)  # allocate 1024 bytes for buffer1
    read1024(buf)
    read1024(buf1)
if __name__ == '__main__':
    main()