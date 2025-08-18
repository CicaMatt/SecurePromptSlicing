import sys

def allocate_and_read():
    import ctypes

    # Allocate first buffer
    buf = ctypes.create_string_buffer(1024)
    # Read up to 100 characters from stdin for the first buffer
    chars_read = sys.stdin.buffer.readinto(buf, 100)

    # Allocate second buffer
    buf1 = ctypes.create_string_buffer(1024)
    # Read up to 100 characters from stdin for the second buffer
    chars_read1 = sys.stdin.buffer.readinto(buf1, 100)

allocate_and_read()