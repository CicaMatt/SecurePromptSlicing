import sys

def allocate_and_read(size):
    import ctypes
    buf = ctypes.create_string_buffer(size)
    data = sys.stdin.buffer.read(size)[:size]
    ctypes.memmove(buf, data, len(data))
    return buf

def main():
    buf = allocate_and_read(1024)
    buf1 = allocate_and_read(1024)

if __name__ == "__main__":
    main()