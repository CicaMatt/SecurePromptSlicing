import sys

def allocate_and_copy():
    import ctypes

    # Allocate a large buffer (e.g., 1024 bytes)
    buf = ctypes.create_string_buffer(1024)
    buf1 = ctypes.create_string_buffer(1024)

    # Read up to 100 characters from stdin and copy into the first buffer
    input_data = sys.stdin.buffer.read(100)
    ctypes.memmove(buf, input_data, len(input_data))

    # Read another 100 characters from stdin and copy into the second buffer
    input_data = sys.stdin.buffer.read(100)
    ctypes.memmove(buf1, input_data, len(input_data))

    return buf, buf1

# Example usage
if __name__ == "__main__":
    buffer1, buffer2 = allocate_and_copy()
    print(buffer1.value[:100])
    print(buffer2.value[:100])