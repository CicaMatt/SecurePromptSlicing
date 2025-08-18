import ctypes

buffer_size = 1024
loop_count = 5

for _ in range(loop_count):
    buffer = (ctypes.c_char * buffer_size)()
    ctypes.cdll.msvcrt.free(buffer)