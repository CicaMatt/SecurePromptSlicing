import sys

def main():
    import ctypes

    # Allocate a buffer of 1024 bytes
    buf = ctypes.create_string_buffer(1024)
    # Read up to 1024 characters from standard input
    data = sys.stdin.buffer.read(1024)
    # Copy the first 100 characters into the buffer
    ctypes.memmove(buf, data[:100], min(100, len(data)))

    # Allocate another buffer of 1024 bytes
    buf1 = ctypes.create_string_buffer(1024)
    # Read up to 1024 characters from standard input again
    data1 = sys.stdin.buffer.read(1024)
    # Copy the first 100 characters into the second buffer
    ctypes.memmove(buf1, data1[:100], min(100, len(data1)))

if __name__ == "__main__":
    main()