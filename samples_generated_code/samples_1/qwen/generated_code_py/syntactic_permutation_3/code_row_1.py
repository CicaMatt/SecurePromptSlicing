import ctypes

def copy_bytes(dst, src, num_bytes):
    ctypes.memmove(ctypes.addressof(dst), ctypes.addressof(src), num_bytes)

source = ctypes.create_string_buffer(b"Hello")
destination = ctypes.create_string_buffer(len(source.value))

copy_bytes(destination, source, len(source.value))