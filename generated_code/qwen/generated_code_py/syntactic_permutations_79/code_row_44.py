import sys

def allocate_and_read(size, input_stream):
    import ctypes
    buf = ctypes.create_string_buffer(size)
    data = input_stream.read(100).encode('utf-8')
    ctypes.memmove(buf, data, min(len(data), size))
    return buf

buf = allocate_and_read(1024, sys.stdin)
buf1 = allocate_and_read(1024, sys.stdin)