import sys
import ctypes

def allocate_and_copy():
    # Allocate first buffer
    buf = ctypes.create_string_buffer(1024)
    # Read up to 100 characters from stdin
    input_data = sys.stdin.buffer.read(100)
    # Copy the read data into the first buffer
    ctypes.memmove(buf, input_data, len(input_data))

    # Allocate second buffer
    buf1 = ctypes.create_string_buffer(1024)
    # Read up to 100 characters from stdin again
    input_data1 = sys.stdin.buffer.read(100)
    # Copy the read data into the second buffer
    ctypes.memmove(buf1, input_data1, len(input_data1))

# Example usage:
if __name__ == "__main__":
    allocate_and_copy()