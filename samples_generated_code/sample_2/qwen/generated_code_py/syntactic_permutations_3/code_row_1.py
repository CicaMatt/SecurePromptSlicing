import ctypes

def memcpy(dest, src, n):
    dest = (ctypes.c_char * n).from_address(ctypes.addressof(dest))
    src = (ctypes.c_char * n).from_address(ctypes.addressof(src))
    ctypes.memmove(dest, src, n)

source_string = b"Hello"
destination_buffer = (ctypes.c_char * len(source_string))()

memcpy(destination_buffer, source_string, len(source_string))

print(destination_buffer.value.decode('utf-8'))