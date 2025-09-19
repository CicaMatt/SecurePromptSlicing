import ctypes

def mem_copy(dest, src, num_bytes):
    ctypes.memmove(dest, src, num_bytes)

buffer = (ctypes.c_char * 10)()
source = b'Hello'
mem_copy(buffer, source, len(source))

print(buffer.value.decode('utf-8'))