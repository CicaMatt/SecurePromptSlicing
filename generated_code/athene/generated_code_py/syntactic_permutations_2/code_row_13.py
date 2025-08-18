import ctypes

def memcpy(dest, src, n):
    dest_buffer = (ctypes.c_ubyte * n).from_address(id(dest))
    src_buffer = (ctypes.c_ubyte * n).from_address(id(src))
    ctypes.memmove(dest_buffer, src_buffer, n)

message = b"Hello, World!"
buffer = bytearray(len(message))

memcpy(buffer, message, len(message))

print(buffer)