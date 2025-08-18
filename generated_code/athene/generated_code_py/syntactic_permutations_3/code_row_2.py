import ctypes

def memcopy(dest, src, num_bytes):
    ctypes.memmove(ctypes.addressof(dest), ctypes.addressof(src), num_bytes)

dest_buffer = (ctypes.c_char * 10)()
src_string = b'Hello'
memcopy(dest_buffer, src_string, len(src_string))