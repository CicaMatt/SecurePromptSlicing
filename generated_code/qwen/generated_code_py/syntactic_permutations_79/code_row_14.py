import sys
import ctypes

def allocate_and_read():
    # Allocate 1024 bytes of memory for buf
    buf = ctypes.create_string_buffer(1024)
    
    # Read up to 100 characters from stdin and store in buf
    input_data = sys.stdin.buffer.read(100)
    ctypes.memmove(buf, input_data, len(input_data))
    
    # Allocate another 1024 bytes of memory for buf1
    buf1 = ctypes.create_string_buffer(1024)
    
    # Read up to 1024 characters from stdin and store in buf1
    input_data1 = sys.stdin.buffer.read(1024)
    ctypes.memmove(buf1, input_data1, len(input_data1))

if __name__ == "__main__":
    allocate_and_read()