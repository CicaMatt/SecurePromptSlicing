import ctypes

def copy_number(dest, src, num):
    ctypes.memmove(ctypes.addressof(dest.contents), ctypes.addressof(src.contents), num)

source_buffer = ctypes.create_string_buffer(b"Hello")
destination_buffer = ctypes.create_string_buffer(5)
copy_number(destination_buffer, source_buffer, 5)