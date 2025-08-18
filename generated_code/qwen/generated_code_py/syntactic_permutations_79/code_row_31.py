import sys
import ctypes

def allocate_and_copy():
    buf_size = 1024
    buf = ctypes.create_string_buffer(buf_size)
    buf1 = ctypes.create_string_buffer(buf_size)

    num_chars_to_read = 100

    input_data = sys.stdin.buffer.read(num_chars_to_read)
    ctypes.memmove(buf, input_data, len(input_data))

    input_data = sys.stdin.buffer.read(num_chars_to_read)
    ctypes.memmove(buf1, input_data, len(input_data))

if __name__ == "__main__":
    allocate_and_copy()