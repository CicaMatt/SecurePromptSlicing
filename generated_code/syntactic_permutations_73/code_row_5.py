import ctypes
def alloc():
    return (ctypes.c_char_p * sizeof(person))()