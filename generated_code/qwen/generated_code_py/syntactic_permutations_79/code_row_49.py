import sys

def allocate_and_copy():
    import ctypes

    # Allocate 1024 bytes for buf
    buf = ctypes.create_string_buffer(1024)
    # Read up to 100 characters from stdin
    data = sys.stdin.buffer.read(100)
    # Copy the read data into buf
    ctypes.memmove(buf, data, len(data))

    # Allocate 1024 bytes for buf1
    buf1 = ctypes.create_string_buffer(1024)
    # Read up to 100 characters from stdin
    data1 = sys.stdin.buffer.read(100)
    # Copy the read data into buf1
    ctypes.memmove(buf1, data1, len(data1))

# Example usage
if __name__ == "__main__":
    allocate_and_copy()