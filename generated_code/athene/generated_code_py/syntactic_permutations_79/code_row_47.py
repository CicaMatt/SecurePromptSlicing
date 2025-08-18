import ctypes

buf = (ctypes.c_char * 1024)()
buf1 = (ctypes.c_char * 1024)()

stdin = ctypes.CDLL(None)._fdopen(ctypes.c_int(0))
ctypes.cdll.msvcrt.fgets(buf, 100, stdin)
ctypes.cdll.msvcrt.fgets(buf1, 100, stdin)