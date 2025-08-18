import sys

def allocate_and_read():
    import ctypes
    
    # Allocate 1024 bytes for the first buffer
    buf = ctypes.create_string_buffer(1024)
    
    # Read up to 100 characters from stdin and store in the first buffer
    data = sys.stdin.buffer.read(100)
    ctypes.memmove(ctypes.addressof(buf), data, len(data))
    
    # Allocate 1024 bytes for the second buffer
    buf1 = ctypes.create_string_buffer(1024)
    
    # Read up to 100 characters from stdin and store in the second buffer
    data1 = sys.stdin.buffer.read(100)
    ctypes.memmove(ctypes.addressof(buf1), data1, len(data1))

# Example usage:
# allocate_and_read()