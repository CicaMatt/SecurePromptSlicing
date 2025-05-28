import ctypes
buffer = (ctypes.c_byte * buffer_size)()
for i in range(buffer_size):
    buffer[i] = ord('.')