import sys

def allocate_and_copy():
    import ctypes

    # Allocate 1024 bytes for the first buffer
    buf = ctypes.create_string_buffer(1024)
    
    # Read 100 characters from stdin and copy to the first buffer
    input_data = sys.stdin.buffer.read(100)
    ctypes.memmove(buf, input_data, len(input_data))

    # Allocate 1024 bytes for the second buffer
    buf1 = ctypes.create_string_buffer(1024)

    # Read next 100 characters from stdin and copy to the second buffer
    input_data = sys.stdin.buffer.read(100)
    ctypes.memmove(buf1, input_data, len(input_data))

# Example usage:
if __name__ == "__main__":
    allocate_and_copy()