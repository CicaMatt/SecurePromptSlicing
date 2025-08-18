import sys

def allocate_and_copy():
    import ctypes

    # Allocate first buffer with 1024 bytes
    buf = ctypes.create_string_buffer(1024)
    
    # Read up to 100 characters from stdin for the first buffer
    input_data = sys.stdin.read(100).encode('utf-8')
    ctypes.memmove(buf, input_data, len(input_data))

    # Allocate second buffer with 1024 bytes
    buf1 = ctypes.create_string_buffer(1024)
    
    # Read up to 100 characters from stdin for the second buffer
    input_data1 = sys.stdin.read(100).encode('utf-8')
    ctypes.memmove(buf1, input_data1, len(input_data1))

# Example usage:
if __name__ == "__main__":
    allocate_and_copy()