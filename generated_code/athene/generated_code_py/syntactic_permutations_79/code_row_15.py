import ctypes

def allocate_buffers_and_read():
    buf = (ctypes.c_char * 1024)()
    buf1 = (ctypes.c_char * 1024)()

    input_data = input()[:1023].encode('utf-8')
    ctypes.memmove(buf, input_data, len(input_data))