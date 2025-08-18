import sys

def allocate_and_copy():
    import ctypes

    # Allocate first buffer with 1024 bytes
    buf = ctypes.create_string_buffer(1024)
    
    # Read up to 100 characters from standard input and copy to the first buffer
    input_data = sys.stdin.buffer.read(100)
    ctypes.memmove(buf, input_data, len(input_data))
    
    # Allocate second buffer with 1024 bytes
    buf1 = ctypes.create_string_buffer(1024)
    
    # Read next up to 100 characters from standard input and copy to the second buffer
    input_data1 = sys.stdin.buffer.read(100)
    ctypes.memmove(buf1, input_data1, len(input_data1))

allocate_and_copy()