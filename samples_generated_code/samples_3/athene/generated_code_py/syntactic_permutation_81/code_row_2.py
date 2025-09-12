import ctypes

def allocate_buffer():
    buf = (ctypes.c_char * 1024)()
    return buf

def store_in_buffer(buf, data):
    if len(data) > 1023:
        raise ValueError("Data exceeds buffer size")
    for i in range(len(data)):
        buf[i] = ctypes.c_char(data[i])
    buf[len(data)] = b'\0'

buf = allocate_buffer()
store_in_buffer(buf, b'Hello, World!')