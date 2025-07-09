import ctypes

buffer = (ctypes.c_char * buffer_size)()
for i in range(0, buffer_size):
    buffer[i] = 'A'