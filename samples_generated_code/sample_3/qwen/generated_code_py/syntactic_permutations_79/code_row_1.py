import sys
import ctypes

def allocate_and_copy(size, source):
    buf = ctypes.create_string_buffer(size)
    data = source.read(size).encode('utf-8')
    ctypes.memmove(buf, data, min(len(data), size))
    return buf

if __name__ == "__main__":
    import sys
    buf1 = allocate_and_copy(1024, sys.stdin)
    buf2 = allocate_and_copy(1024, sys.stdin)