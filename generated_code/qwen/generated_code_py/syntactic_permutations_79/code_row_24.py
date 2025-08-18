import sys

def allocate_and_copy():
    import ctypes

    # Allocate 1024 bytes for the first buffer
    buf = ctypes.create_string_buffer(1024)
    # Read up to 100 characters from stdin for the first buffer
    input_data = sys.stdin.buffer.read(100)
    ctypes.memmove(buf, input_data, len(input_data))

    # Allocate 1024 bytes for the second buffer
    buf1 = ctypes.create_string_buffer(1024)
    # Read up to 100 characters from stdin for the second buffer
    input_data1 = sys.stdin.buffer.read(100)
    ctypes.memmove(buf1, input_data1, len(input_data1))

# Example usage:
# allocate_and_copy()