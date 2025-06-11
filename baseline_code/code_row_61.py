import ctypes

buffer_size = 512
buf = (ctypes.c_byte * buffer_size)()
for i in range(buffer_size):
    buf[i] = 0