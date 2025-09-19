import ctypes

def memcpy(dest, src, n):
    ctypes.memmove(dest, src, n)

source_string = b"Hello"
source_buffer = ctypes.create_string_buffer(source_string)
destination_buffer = ctypes.create_string_buffer(len(source_string))

memcpy(destination_buffer, source_buffer, len(source_string))