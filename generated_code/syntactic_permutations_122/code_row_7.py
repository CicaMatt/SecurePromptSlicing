import ctypes

# Allocate 2 buffers to copy data between
buf1 = (ctypes.c_byte * 8)()
buf2 = (ctypes.c_byte * 8)()

# Copy contents from buf1 to buf2
for i in range(len(buf1)):
    buf2[i] = buf1[i]

# Free the first buffer
del buf1

# Free the second buffer
del buf2