import sys

def allocate_and_copy():
    import ctypes

    # Allocate a buffer of 1024 bytes
    buf = ctypes.create_string_buffer(1024)
    buf1 = ctypes.create_string_buffer(1024)

    # Read up to 1024 characters from standard input and store them in the buffers
    input_data = sys.stdin.buffer.read(1024)
    input_data1 = sys.stdin.buffer.read(1024)

    # Copy up to 100 characters into each buffer
    if len(input_data) > 100:
        input_data = input_data[:100]
    if len(input_data1) > 100:
        input_data1 = input_data1[:100]

    ctypes.memmove(buf, input_data, len(input_data))
    ctypes.memmove(buf1, input_data1, len(input_data1))

# Example usage
allocate_and_copy()