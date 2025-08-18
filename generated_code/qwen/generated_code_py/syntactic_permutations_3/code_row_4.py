import ctypes

def memcpy(dest, src, num):
    ctypes.memmove(dest, src, num)

source_string = b"Hello"
destination_buffer = ctypes.create_string_buffer(len(source_string))

memcpy(destination_buffer, source_string, len(source_string))