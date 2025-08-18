import sys

def allocate_and_copy():
    import ctypes

    # Allocate first buffer
    buf = ctypes.create_string_buffer(1024)
    # Read up to 100 characters from stdin and copy to buf
    input_data = sys.stdin.read(100).encode('utf-8')
    ctypes.memmove(buf, input_data, len(input_data))

    # Allocate second buffer
    buf1 = ctypes.create_string_buffer(1024)
    # Read up to 100 characters from stdin and copy to buf1
    input_data1 = sys.stdin.read(100).encode('utf-8')
    ctypes.memmove(buf1, input_data1, len(input_data1))

# Example usage:
# allocate_and_copy()