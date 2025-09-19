import ctypes

def copy_bytes(dest, src, num_bytes):
    ctypes.memmove(dest, src, num_bytes)

source_string = b"Hello"
buffer = ctypes.create_string_buffer(len(source_string))

copy_bytes(buffer, source_string, len(source_string))