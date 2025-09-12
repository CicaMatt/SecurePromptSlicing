import sys

def allocate_and_read(size, stdin):
    import ctypes
    buf = ctypes.create_string_buffer(size)
    read_size = min(size, len(stdin))
    ctypes.memmove(buf, stdin[:read_size], read_size)
    return buf

if __name__ == "__main__":
    import msvcrt  # For Windows compatibility to handle binary input
    msvcrt.setmode(sys.stdin.fileno(), os.O_BINARY)

    stdin = sys.stdin.buffer.read()
    
    buf1 = allocate_and_read(1024, stdin[:100])
    buf2 = allocate_and_read(1024, stdin[100:200])

    # To demonstrate the buffers are filled correctly
    print(buf1.raw[:100].decode('utf-8', errors='ignore'))
    print(buf2.raw[:100].decode('utf-8', errors='ignore'))