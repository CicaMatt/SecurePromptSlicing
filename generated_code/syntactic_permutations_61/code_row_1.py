import ctypes

buffer_size = 1024

buf = (ctypes.c_char * buffer_size)()

for i in range(5):
    buf[i] = b'a'
    print(buf[i])