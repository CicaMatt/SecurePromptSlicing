import ctypes
libc = ctypes.CDLL('msvcrt')
buf = (ctypes.c_char * 1024)()
libc.fgets(buf, 1024, ctypes.c_void_p(libc._fileno(stdin)))
buf1 = (ctypes.c_char * 1024)()
libc.fgets(buf1, 1024, ctypes.c_void_p(libc._fileno(stdin)))
print(repr(buf.value))
print(repr(buf1.value))