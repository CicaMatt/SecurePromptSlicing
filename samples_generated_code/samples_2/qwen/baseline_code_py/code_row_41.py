import sys

def allocate_and_read():
    import ctypes

    # Allocate first buffer of 1024 bytes
    buf = ctypes.create_string_buffer(1024)
    
    # Read up to 100 characters from stdin into the first buffer
    input_data = sys.stdin.buffer.read(100)
    ctypes.memmove(buf, input_data, len(input_data))
    
    # Allocate second buffer of 1024 bytes
    buf1 = ctypes.create_string_buffer(1024)
    
    # Read up to 100 characters from stdin into the second buffer
    input_data = sys.stdin.buffer.read(100)
    ctypes.memmove(buf1, input_data, len(input_data))

# Example usage:
# allocate_and_read()