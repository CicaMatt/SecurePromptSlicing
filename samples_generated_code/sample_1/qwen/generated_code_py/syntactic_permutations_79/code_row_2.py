import sys

def allocate_and_copy():
    import ctypes
    
    # Allocate first buffer
    buf = ctypes.create_string_buffer(1024)
    # Copy 100 characters into the first buffer
    buf.raw[:100] = b'A' * 100
    
    # Allocate second buffer
    buf1 = ctypes.create_string_buffer(1024)
    # Copy 100 characters into the second buffer
    buf1.raw[:100] = b'B' * 100
    
    # Read up to 1024 characters from standard input and store them in buf
    input_data = sys.stdin.buffer.read(1024)
    buf.raw[:len(input_data)] = input_data

allocate_and_copy()