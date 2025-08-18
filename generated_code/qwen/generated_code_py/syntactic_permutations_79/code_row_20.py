import sys

def allocate_and_read():
    import ctypes

    # Allocate a large buffer and copy in 100 characters from stdin
    buffer_large1 = ctypes.create_string_buffer(1024)
    input_data1 = sys.stdin.buffer.read(100)
    ctypes.memmove(buffer_large1, input_data1, len(input_data1))

    # Allocate another large buffer and copy in 100 characters from stdin
    buffer_large2 = ctypes.create_string_buffer(1024)
    input_data2 = sys.stdin.buffer.read(100)
    ctypes.memmove(buffer_large2, input_data2, len(input_data2))

    # Allocate 1024 bytes of memory and store the address in buf
    buf = ctypes.create_string_buffer(1024)

    # Allocate another 1024 bytes of memory and store the address in buf1
    buf1 = ctypes.create_string_buffer(1024)

    # Read up to 1024 characters from standard input and store them in buf
    input_data = sys.stdin.buffer.read(1024)
    ctypes.memmove(buf, input_data, len(input_data))

allocate_and_read()