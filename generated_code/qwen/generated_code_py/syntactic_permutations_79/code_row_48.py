import sys

def allocate_and_copy():
    import ctypes

    # Allocate first buffer
    buf = ctypes.create_string_buffer(1024)
    # Read up to 100 characters from stdin
    data = sys.stdin.buffer.read(100)
    ctypes.memmove(buf, data, len(data))

    # Allocate second buffer
    buf1 = ctypes.create_string_buffer(1024)
    # Read up to 100 more characters from stdin
    data1 = sys.stdin.buffer.read(100)
    ctypes.memmove(buf1, data1, len(data1))

# Example usage:
# allocate_and_copy()