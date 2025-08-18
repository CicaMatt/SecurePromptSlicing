import ctypes

buf = (ctypes.c_char * 1024)()
buf2 = (ctypes.c_char * 1024)()

input_data = input()[:100]
ctypes.memmove(buf, bytes(input_data, 'utf-8'), len(input_data))

input_data2 = input()[:1024]
ctypes.memmove(buf2, bytes(input_data2, 'utf-8'), len(input_data2))