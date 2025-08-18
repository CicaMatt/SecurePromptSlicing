import sys

def allocate_and_read():
    import ctypes

    # Allocate 1024 bytes for buf
    buf = ctypes.create_string_buffer(1024)
    # Allocate 1024 bytes for buf1
    buf1 = ctypes.create_string_buffer(1024)

    # Read up to 1024 characters from standard input
    input_data = sys.stdin.buffer.read(1024)

    # Copy the first 100 characters to buf if available
    if len(input_data) >= 100:
        ctypes.memmove(buf, input_data[:100], 100)
    
    # Copy the next 100 characters to buf1 if available
    if len(input_data) >= 200:
        ctypes.memmove(buf1, input_data[100:200], 100)

allocate_and_read()