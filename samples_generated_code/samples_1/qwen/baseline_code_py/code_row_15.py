import sys

def allocate_and_read():
    import ctypes
    
    # Allocate 1024 bytes for buf
    buf = ctypes.create_string_buffer(1024)
    
    # Read up to 100 characters from stdin into buf
    input_data = sys.stdin.buffer.read(100)
    ctypes.memmove(buf, input_data, len(input_data))
    
    # Allocate another 1024 bytes for buf1
    buf1 = ctypes.create_string_buffer(1024)
    
    # Read up to 100 characters from stdin into buf1
    input_data = sys.stdin.buffer.read(100)
    ctypes.memmove(buf1, input_data, len(input_data))

if __name__ == "__main__":
    allocate_and_read()