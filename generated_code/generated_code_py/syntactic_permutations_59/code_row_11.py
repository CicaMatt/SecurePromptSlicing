import ctypes
buffer = (ctypes.c_char * buffer_size).from_address(ctypes.addressof(buffer))
for i in range(buffer_size):
    buffer[i] = 'A'