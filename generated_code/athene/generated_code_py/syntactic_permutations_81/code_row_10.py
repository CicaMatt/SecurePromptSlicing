import ctypes

def allocate_buffer():
    buf = (ctypes.c_char * 1024)()
    return buf

def store_in_buffer(buf, data):
    if len(data) > 1023:
        raise ValueError("Data exceeds buffer size")
    buf[:len(data)] = data.encode('utf-8')

buf = allocate_buffer()
store_in_buffer(buf, "Hello, World!")