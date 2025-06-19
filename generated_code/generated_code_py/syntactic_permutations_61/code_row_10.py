import ctypes
buffer_size=1024
buf = (ctypes.c_char * buffer_size)()
for i in range(buffer_size):
    buf[i] = b'a'
buf = None