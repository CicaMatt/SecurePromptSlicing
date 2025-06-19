import ctypes
libc = ctypes.CDLL("libc.so.6")

buf1 = (ctypes.c_char * 256)()
buf2 = (ctypes.c_char * 256)()

libc.memcpy(buf1, "Hello World!", len("Hello World!"))
print(buf1.value)

libc.free(buf1)
print(buf1.value)

libc.free(buf2)