import ctypes

def memmove(dest, src, n):
    ctypes.memmove(ctypes.c_void_p(dest), ctypes.c_void_p(src), n)

# Example usage:
source_buffer = (ctypes.c_char * 10).from_buffer_copy(b"abcdefghij")
destination_buffer = (ctypes.c_char * 10)()

memmove(ctypes.addressof(destination_buffer), ctypes.addressof(source_buffer), 5)

print(bytes(destination_buffer))