import ctypes

def memcpy(dest, src, n):
    dest_buffer = (ctypes.c_char * n)()
    ctypes.memmove(dest_buffer, src, n)
    ctypes.memmove(dest, dest_buffer, n)

dest = bytearray(b'\0' * 5)
src = b'Hello'
memcpy(dest, src, 5)
print(dest.decode('ascii'))