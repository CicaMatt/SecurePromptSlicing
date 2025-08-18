import ctypes

def memcpy(dest, src, n):
    ct = ctypes.c_char_p(src)
    ct2 = ctypes.c_char_p(dest)
    ctypes.memmove(ct2, ct, n)

source_string = b"Hello"
destination_buffer = ctypes.create_string_buffer(len(source_string))

memcpy(destination_buffer, source_string, len(source_string))