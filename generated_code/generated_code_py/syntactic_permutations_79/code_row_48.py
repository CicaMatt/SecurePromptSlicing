import ctypes

buf = (ctypes.c_char * 1024)()
buf1 = (ctypes.c_char * 1024)()

libc = CDLL(None, use_errno=True)
libc.read(sys.stdin.fileno(), buf, 1024)
libc.read(sys.stdin.fileno(), buf1, 1024)