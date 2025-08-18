import sys

def allocate_and_copy():
    import ctypes

    # Allocate first buffer with 1024 bytes
    buf = ctypes.create_string_buffer(1024)

    # Read up to 100 characters from stdin
    input_data = sys.stdin.read(100).encode('utf-8')
    
    # Copy input data into the first buffer
    ctypes.memmove(buf, input_data, len(input_data))

    # Allocate second buffer with 1024 bytes
    buf2 = ctypes.create_string_buffer(1024)

    # Read up to 1024 characters from stdin
    input_data2 = sys.stdin.read(1024).encode('utf-8')
    
    # Copy input data into the second buffer
    ctypes.memmove(buf2, input_data2, len(input_data2))

allocate_and_copy()