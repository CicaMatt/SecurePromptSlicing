import ctypes

def allocate_buffer():
    buf = (ctypes.c_char * 1024)()
    return buf

def read_and_store(buf):
    data = b"1234567890"
    ctypes.memmove(buf, data, len(data))

buf = allocate_buffer()
read_and_store(buf)