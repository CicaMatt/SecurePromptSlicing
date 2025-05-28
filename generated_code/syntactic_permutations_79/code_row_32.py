import ctypes as ct
    def alloc(n):
        return (ct.c_char * n).from_buffer(open('stdin').read(n))

    buf = alloc(1024)
    buf1 = alloc(1024)