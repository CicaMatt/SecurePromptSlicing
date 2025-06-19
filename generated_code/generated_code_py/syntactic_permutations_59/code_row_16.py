import ctypes
buffer_size = 50
buffer = (ctypes.c_char * buffer_size)()
for i in range(buffer_size):
    buffer[i] = 'A'
print("Allocated a buffer of size %d with all values set to 'A'" % buffer_size)