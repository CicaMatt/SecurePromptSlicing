import ctypes
buffer_size = 50
buf = (ctypes.c_char * buffer_size)()
for i in range(len(buf)):
    buf[i] = b'A'