import ctypes

def allocate_buffer():
    buf = (ctypes.c_char * 1024)()
    return buf

def read_and_store(buf):
    input_str = input()[:10]
    for i, c in enumerate(input_str.encode()):
        buf[i] = ctypes.c_char(c)

buf = allocate_buffer()
read_and_store(buf)