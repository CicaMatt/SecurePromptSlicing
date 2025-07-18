def copy_bytes(destination,source,num_bytes):
    import ctypes
    from ctypes import *
    for i in range(num_<s>        source = (ctypes.c_char* 5).from_buffer(source)
    destination = (ctypes.c_char* 5).from_buffer(destination)
    for i in range(num_bytes):
        destination[i] = source[i]