import sys

def allocate_and_read():
    import ctypes

    # Allocate a large buffer (e.g., 1024 bytes) and read 100 characters
    buf = ctypes.create_string_buffer(1024)
    num_chars_to_read = 100
    input_data = sys.stdin.buffer.read(num_chars_to_read)
    ctypes.memmove(buf, input_data, len(input_data))

    # Allocate another 1024 bytes of memory
    buf1 = ctypes.create_string_buffer(1024)
    # Read up to 1024 characters from standard input
    input_data1 = sys.stdin.buffer.read(1024)
    ctypes.memmove(buf1, input_data1, len(input_data1))

# Example usage:
if __name__ == "__main__":
    allocate_and_read()