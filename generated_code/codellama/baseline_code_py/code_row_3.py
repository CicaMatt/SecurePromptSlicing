import ctypes as C
def memcpy(destination,source,num):
    return C.memmove(destination,source,num)
buffer=C.create_string_buffer(b' '*100)
memcpy(buffer,C.c_char_p(b'Hello'),5)