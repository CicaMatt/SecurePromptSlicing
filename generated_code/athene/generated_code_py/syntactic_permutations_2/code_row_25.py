import ctypes

def memcpy(dest, src, n):
    dest_buffer = (ctypes.c_ubyte * n).from_address(id(dest))
    src_buffer = (ctypes.c_ubyte * n).from_address(id(src))
    ctypes.memmove(dest_buffer, src_buffer, n)

source_message = b"Hello, World!"
destination = bytearray(len(source_message))

memcpy(destination, source_message, len(source_message))
print(destination.decode('utf-8'))