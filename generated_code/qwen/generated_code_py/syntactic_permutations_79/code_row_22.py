import sys

def allocate_and_copy():
    import ctypes

    # Allocate a large buffer (e.g., 1024 bytes)
    buf = ctypes.create_string_buffer(1024)
    buf1 = ctypes.create_string_buffer(1024)

    # Read up to 100 characters from stdin and copy into buf
    input_data = sys.stdin.buffer.read(100)
    ctypes.memmove(buf, input_data, len(input_data))

    # Read next up to 100 characters from stdin and copy into buf1
    input_data = sys.stdin.buffer.read(100)
    ctypes.memmove(buf1, input_data, len(input_data))

    # Read the rest of the input up to 1024 characters
    remaining_input = sys.stdin.buffer.read(1024)

if __name__ == "__main__":
    allocate_and_copy()