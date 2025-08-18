import ctypes

buffer_size = 1024

# Allocate first buffer
buf1 = (ctypes.c_char * buffer_size)()
read1 = ctypes.c_int(ctypes.stdin.readinto(buf1[:100]))

# Allocate second buffer
buf2 = (ctypes.c_char * buffer_size)()
read2 = ctypes.c_int(ctypes.stdin.readinto(buf2[:100]))