import ctypes

def memcpy(dest, src, num):
    ctypes.memmove(dest, src, num)

buffer = (ctypes.c_char * 10)()
source = b'Hello'
memcpy(buffer, source, len(source))
print(buffer.value.decode('utf-8'))