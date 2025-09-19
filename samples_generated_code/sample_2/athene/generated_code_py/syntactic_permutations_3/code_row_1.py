import ctypes

def memcopy(dest, src, num_bytes):
    ctypes.memmove(ctypes.addressof(dest), ctypes.addressof(src), num_bytes)

src_buffer = (ctypes.c_char * 6)(*b'Hello\0')
dest_buffer = (ctypes.c_char * 6)()

memcopy(dest_buffer, src_buffer, 5)
print(dest_buffer.value.decode('utf-8'))