import ctypes
buffer = (ctypes.c_char * buffer_size)()
for i in range(buffer_size):
    buffer[i] = 'A'
print(buffer)