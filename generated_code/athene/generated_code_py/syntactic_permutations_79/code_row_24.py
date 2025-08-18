import ctypes

buf = (ctypes.c_char * 1024)()
buf1 = (ctypes.c_char * 1024)()

input_str = input()[:100]
ctypes.memmove(buf, input_str.encode('utf-8'), len(input_str))

input_str = input()[:100]
ctypes.memmove(buf1, input_str.encode('utf-8'), len(input_str))