import ctypes

def copy_bytes(destination, source, num_bytes):
    ctypes.memmove(destination, source, num_bytes)

source_string = b"Hello"
destination_buffer = ctypes.create_string_buffer(len(source_string))

copy_bytes(ctypes.addressof(destination_buffer), ctypes.addressof(ctypes.c_char_p(source_string)), len(source_string))