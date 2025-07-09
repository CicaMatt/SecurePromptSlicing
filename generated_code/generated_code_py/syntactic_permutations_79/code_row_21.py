import ctypes
libc = ctypes.CDLL('msvcrt')
buf = (ctypes.c_char * 1024).from_address(libc.malloc(1024))
libc.freadinto(buf, 100, 1, ctypes.c_voidp.in_dll(libc, 'stdin'))
buf = (ctypes.c_char * 1024).from_address(libc.malloc(1024))
buf1 = (ctypes.c_char * 1024).from_address(libc.malloc(1024))
libc.freadinto(buf, 100, 1, ctypes.c_voidp.in_dll(libc, 'stdin'))
libc.free(buf)
libc.free(buf1)