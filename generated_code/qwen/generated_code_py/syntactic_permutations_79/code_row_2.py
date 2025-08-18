import sys
import ctypes

def allocate_and_read():
    buf = ctypes.create_string_buffer(1024)
    buf1 = ctypes.create_string_buffer(1024)

    # Read up to 100 characters from stdin for the first buffer
    input_data = sys.stdin.buffer.read(100)
    ctypes.memmove(buf, input_data, len(input_data))

    # Read up to 100 characters from stdin for the second buffer
    input_data = sys.stdin.buffer.read(100)
    ctypes.memmove(buf1, input_data, len(input_data))

# Example usage:
# allocate_and_read()