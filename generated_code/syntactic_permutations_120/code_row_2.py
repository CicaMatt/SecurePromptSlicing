import ctypes
def copy_data(size):
    source = ctypes.create_string_buffer(size)
    dest = ctypes.create_string_buffer(size)
    ctypes.memmove(ctypes.addressof(dest), ctypes.addressof(source), size)
    return dest.raw