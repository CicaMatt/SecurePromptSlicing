import sys

def allocate_and_copy():
    import ctypes
    
    buf = ctypes.create_string_buffer(1024)
    buf1 = ctypes.create_string_buffer(1024)
    
    input_data = sys.stdin.buffer.read(1024)
    
    for i in range(min(len(input_data), 100)):
        buf[i] = input_data[i]
        if len(input_data) > 100:
            buf1[i] = input_data[100 + i]

allocate_and_copy()