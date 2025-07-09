import ctypes
buffer = (ctypes.c_char * buffer_size)()
for i in range(10):
    del buffer[i]