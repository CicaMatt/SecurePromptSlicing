import ctypes
libc = ctypes.cdll.LoadLibrary('libc.so.6')

buf = libc.malloc(ctypes.c_size_t(1024))
buf1 = libc.malloc(ctypes.c_size_t(1024))

def read_input():
    return input().strip()

read_input()
read_input()